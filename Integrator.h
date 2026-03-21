#pragma once
#include <vector>
#include "Body.h"
#include "Field.h"

// 积分器基类
class Integrator
{
public:
    virtual ~Integrator() = default;
    virtual void update(Body& body, double dt,
        const std::vector<Field*>& fields) = 0;
};

// ----------------------------------------------
// Boris 方法（用于存在磁场的场景，同时支持电场和重力）
// 完全移植自您原有代码中的 Boris 算法
// ----------------------------------------------
class BorisIntegrator : public Integrator
{
public:
    void update(Body& body, double dt,
        const std::vector<Field*>& fields) override;
};

// ----------------------------------------------
// 欧拉方法（用于无磁场的场景，支持电场和重力）
// ----------------------------------------------
class EulerIntegrator : public Integrator
{
public:
    void update(Body& body, double dt,
        const std::vector<Field*>& fields) override;
};