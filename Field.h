#pragma once

// 物理场基类，只提供参数查询接口
class Field
{
public:
    virtual ~Field() = default;

    // 重力加速度
    virtual double getG() const { return 0.0; }
    // 磁场强度（标量，假设垂直于平面）
    virtual double getB() const { return 0.0; }
    // 电场强度分量
    virtual double getEx() const { return 0.0; }
    virtual double getEy() const { return 0.0; }
};