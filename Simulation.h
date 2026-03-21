#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Body.h"
#include "Field.h"

class Simulation
{
public:
    explicit Simulation(double dt);
    ~Simulation();

    // 添加物理场（所有权转移）
    void addField(Field* field);
    // 设置待仿真的物体（指针列表，不管理生命周期）
    void setBodies(const std::vector<Body*>& bodies);

    // 运行仿真，结果输出到以 prefix 为前缀的文件
    void run(int steps, const std::string& prefix);

private:
    double dt_;
    std::vector<std::unique_ptr<Field>> fields_;   // 存储场（自动释放）
    std::vector<Body*> bodies_;                    // 外部管理生命周期
};