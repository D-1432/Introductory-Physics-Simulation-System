#include "BodyManager.h"
#include "Particle.h"
#include"Constants.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

BodyManager::BodyManager() = default;
BodyManager::~BodyManager() = default;

void BodyManager::loadFromFile(const string& filename)
{
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        // 文件不存在，视为空
        bodies_.clear();
        return;
    }

    bodies_.clear();
    int id;
    string name;
    double m, x, y, vx, vy, q, fx, fy;
    while (ifs >> id >> name >> m >> x >> y >> vx >> vy >> q >> fx >> fy) {
        if (name == "粒子") {
            auto body = make_unique<Particle>(id, m, x, y, vx, vy, q, fx, fy);
            bodies_.push_back(std::move(body));
        }
        // 可扩展其他类型
    }
    ifs.close();
}

void BodyManager::saveToFile(const string& filename) const
{
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cerr << "无法保存文件：" << filename << endl;
        return;
    }
    for (const auto& body : bodies_) {
        ofs << body->m_ID << "\t"
            << body->m_Name << "\t"
            << body->m_Mass << "\t"
            << body->m_X << " " << body->m_Y << "\t"
            << body->m_Vx << " " << body->m_Vy << "\t"
            << body->m_Q << "\t"
            << body->m_Fx << " " << body->m_Fy << "\n";
    }
    ofs.close();
}

bool BodyManager::idExists(int id) const
{
    return find_if(bodies_.begin(), bodies_.end(),
        [id](const auto& b) { return b->m_ID == id; }) != bodies_.end();
}

int BodyManager::generateNewId() const
{
    int maxId = 0;
    for (const auto& b : bodies_) {
        if (b->m_ID > maxId) maxId = b->m_ID;
    }
    return maxId + 1;
}

void BodyManager::addObject()
{
    int id = generateNewId();
    double m, x, y, vx, vy, q, fx, fy;
    int hasInitForce;

    cout << "新增物体（编号将自动分配为 " << id << "）" << endl;
    cout << "质量 mass = "; cin >> m;
    cout << "坐标 x = "; cin >> x;
    cout << "     y = "; cin >> y;
    cout << "速度 vx = "; cin >> vx;
    cout << "     vy = "; cin >> vy;
    cout << "电荷量 q = "; cin >> q;
    cout << "是否有初始受力？(1:是 2:否): "; cin >> hasInitForce;
    if (hasInitForce == 1) {
        cout << "fx = "; cin >> fx;
        cout << "fy = "; cin >> fy;
    }
    else {
        fx = fy = 0;
    }

    int type;
    cout << "选择类型: 1.粒子 (其他类型开发中): "; cin >> type;
    if (type == 1) {
        bodies_.push_back(make_unique<Particle>(id, m, x, y, vx, vy, q, fx, fy));
        cout << "添加成功！" << endl;
    }
    else {
        cout << "暂不支持该类型。" << endl;
    }
    saveToFile(FILENAME1);
}

bool BodyManager::removeObject(int id)
{
    auto it = find_if(bodies_.begin(), bodies_.end(),
        [id](const auto& b) { return b->m_ID == id; });
    if (it == bodies_.end()) return false;
    bodies_.erase(it);
    saveToFile(FILENAME1);
    return true;
}

bool BodyManager::modifyObject(int id)
{
    auto it = find_if(bodies_.begin(), bodies_.end(),
        [id](const auto& b) { return b->m_ID == id; });
    if (it == bodies_.end()) return false;

    // 重新输入所有信息
    double m, x, y, vx, vy, q, fx, fy;
    int hasInitForce;
    cout << "修改物体（编号 " << id << "）" << endl;
    cout << "新质量 = "; cin >> m;
    cout << "新坐标 x = "; cin >> x;
    cout << "        y = "; cin >> y;
    cout << "新速度 vx = "; cin >> vx;
    cout << "        vy = "; cin >> vy;
    cout << "新电荷量 q = "; cin >> q;
    cout << "是否有初始受力？(1:是 2:否): "; cin >> hasInitForce;
    if (hasInitForce == 1) {
        cout << "fx = "; cin >> fx;
        cout << "fy = "; cin >> fy;
    }
    else {
        fx = fy = 0;
    }

    int type;
    cout << "新类型: 1.粒子: "; cin >> type;
    if (type == 1) {
        *it = make_unique<Particle>(id, m, x, y, vx, vy, q, fx, fy);
        cout << "修改成功！" << endl;
    }
    else {
        cout << "暂不支持该类型。" << endl;
    }
    saveToFile(FILENAME1);
    return true;
}

bool BodyManager::findAndShow(int id) const
{
    auto it = find_if(bodies_.begin(), bodies_.end(),
        [id](const auto& b) { return b->m_ID == id; });
    if (it == bodies_.end()) return false;
    (*it)->showInfo();
    return true;
}

void BodyManager::showAll() const
{
    if (bodies_.empty()) {
        cout << "暂无物体数据。" << endl;
        return;
    }
    for (const auto& b : bodies_) {
        b->showInfo();
    }
}

vector<Body*> BodyManager::getBodies() const
{
    vector<Body*> ptrs;
    for (const auto& b : bodies_) {
        ptrs.push_back(b.get());
    }
    return ptrs;
}