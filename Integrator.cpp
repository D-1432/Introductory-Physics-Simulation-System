#include "Integrator.h"
#include <cmath>

// ---------- Boris 方法 ----------
void BorisIntegrator::update(Body& body, double dt,
    const std::vector<Field*>& fields)
{
    // 汇总场参数
    double G = 0.0, B = 0.0, Ex = 0.0, Ey = 0.0;
    for (auto f : fields) {
        G += f->getG();
        B += f->getB();
        Ex += f->getEx();
        Ey += f->getEy();
    }

    double m = body.m_Mass;
    double q = body.m_Q;
    double vx = body.m_Vx;
    double vy = body.m_Vy;
    double x = body.m_X;
    double y = body.m_Y;

    // 如果磁场为零，Boris 方法退化为普通欧拉（但此处假设调用者已保证 B != 0）
    // 但为安全，若 B == 0，则直接使用欧拉更新
    if (B == 0.0) {
        // 退化为欧拉
        double ax = q * Ex / m;
        double ay = q * Ey / m + G;
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;
        body.m_Vx = vx; body.m_Vy = vy;
        body.m_X = x;   body.m_Y = y;
        return;
    }

    // ---------- Boris 方法核心（完全保留您的算法）----------
    double half_dt = 0.5 * dt;

    // 半加速度（电场 + 重力）
    vy += ((Ey * q / m) + G) * half_dt;
    vx += (Ex * q / m) * half_dt;

    // 磁场旋转
    double v = sqrt(vx * vx + vy * vy);
    double r = (m * v) / (q * B);
    double w = v / r;
    double theta = w * dt;
    double vx_new = vx * cos(theta) - vy * sin(theta);
    double vy_new = vx * sin(theta) + vy * cos(theta);
    vx = vx_new;
    vy = vy_new;

    // 另一半加速度
    vy += ((Ey * q / m) + G) * half_dt;
    vx += (Ex * q / m) * half_dt;

    // 更新位置
    x += vx * dt;
    y += vy * dt;

    // 写回 Body
    body.m_Vx = vx;
    body.m_Vy = vy;
    body.m_X = x;
    body.m_Y = y;
}

// ---------- 欧拉方法 ----------
void EulerIntegrator::update(Body& body, double dt,
    const std::vector<Field*>& fields)
{
    // 汇总场参数
    double G = 0.0, Ex = 0.0, Ey = 0.0;
    for (auto f : fields) {
        G += f->getG();
        Ex += f->getEx();
        Ey += f->getEy();
    }

    double m = body.m_Mass;
    double q = body.m_Q;
    double ax = q * Ex / m;
    double ay = q * Ey / m + G;

    // 更新速度（欧拉法）
    body.m_Vx += ax * dt;
    body.m_Vy += ay * dt;

    // 更新位置
    body.m_X += body.m_Vx * dt;
    body.m_Y += body.m_Vy * dt;
}