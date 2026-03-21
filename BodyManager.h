#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Body.h"

class BodyManager
{
public:
    BodyManager();
    ~BodyManager();

    // 从文件加载物体
    void loadFromFile(const std::string& filename);
    // 保存物体到文件
    void saveToFile(const std::string& filename) const;

    // 增加物体（自动分配 ID 并存储）
    void addObject();
    // 删除物体（按 ID）
    bool removeObject(int id);
    // 修改物体（按 ID，需重新输入所有信息）
    bool modifyObject(int id);
    // 按 ID 查找并显示
    bool findAndShow(int id) const;
    // 显示所有物体
    void showAll() const;

    // 获取所有物体指针（供仿真使用）
    std::vector<Body*> getBodies() const;

    // 获取物体数量
    int getCount() const { return static_cast<int>(bodies_.size()); }
    // 判断文件是否为空
    bool isEmpty() const { return bodies_.empty(); }

private:
    std::vector<std::unique_ptr<Body>> bodies_;

    // 辅助函数：判断编号是否已存在
    bool idExists(int id) const;
    // 生成新编号（最大编号+1）
    int generateNewId() const;
};