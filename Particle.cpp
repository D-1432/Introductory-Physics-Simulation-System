#include "Particle.h"

Particle::Particle(int id, double mass, double x0, double y0,
    double vx0, double vy0, double q, double fx, double fy)
{
    m_ID = id;
    m_Name = "粒子";
    m_Mass = mass;
    m_X = x0;
    m_Y = y0;
    m_Vx = vx0;
    m_Vy = vy0;
    m_Q = q;
    m_Fx = fx;
    m_Fy = fy;
}

void Particle::showInfo()
{
    cout << "编号：" << m_ID
        << "\t类型：" << m_Name
        << "\t质量：" << m_Mass
        << "\t坐标：(" << m_X << "," << m_Y << ")"
        << "\t速度：(" << m_Vx << "," << m_Vy << ")"
        << "\t电荷量：" << m_Q << endl;
}