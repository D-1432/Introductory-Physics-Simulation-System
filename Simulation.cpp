#include "Simulation.h"
#include "Integrator.h"
#include <fstream>
#include <iostream>

Simulation::Simulation(double dt) : dt_(dt) {}

Simulation::~Simulation() = default;

void Simulation::addField(Field* field)
{
    fields_.emplace_back(field);
}

void Simulation::setBodies(const std::vector<Body*>& bodies)
{
    bodies_ = bodies;
}

void Simulation::run(int steps, const std::string& prefix)
{
    if (bodies_.empty()) {
        std::cout << "没有物体可仿真！" << std::endl;
        return;
    }

    // 根据场组合选择积分器
    std::unique_ptr<Integrator> integrator;
    bool hasMagnetic = false;
    for (const auto& f : fields_) {
        if (f->getB() != 0.0) {
            hasMagnetic = true;
            break;
        }
    }

    if (hasMagnetic) {
        integrator = std::make_unique<BorisIntegrator>();
    }
    else {
        integrator = std::make_unique<EulerIntegrator>();
    }

    // 为了将场传递给积分器，需要将 unique_ptr 转为原始指针
    std::vector<Field*> rawFields;
    for (const auto& f : fields_) {
        rawFields.push_back(f.get());
    }

    // 对每个物体独立输出轨迹
    for (size_t i = 0; i < bodies_.size(); ++i) {
        Body* b = bodies_[i];
        if (!b) continue;

        std::string filename = prefix + std::to_string(i) + ".txt";
        std::ofstream ofs(filename);
        if (!ofs.is_open()) {
            std::cerr << "无法打开文件 " << filename << " 写入！" << std::endl;
            continue;
        }

        ofs << "# t\tx\ty\tvx\tvy\n";

        // 拷贝初始状态，防止污染原物体（若需要保留原状态，可在此拷贝）
        double x = b->m_X, y = b->m_Y;
        double vx = b->m_Vx, vy = b->m_Vy;
        double q = b->m_Q, m = b->m_Mass;

        // 临时 Body 对象，用于积分器更新
        Body temp = *b;

        for (int step = 0; step <= steps; ++step) {
            // 写入当前步
            ofs << step * dt_ << "\t"
                << temp.m_X << "\t" << temp.m_Y << "\t"
                << temp.m_Vx << "\t" << temp.m_Vy << "\n";

            // 更新一步
            integrator->update(temp, dt_, rawFields);
        }
        ofs.close();
    }
    std::cout << "仿真完成，结果已保存至 " << prefix << "*.txt 文件。" << std::endl;
}