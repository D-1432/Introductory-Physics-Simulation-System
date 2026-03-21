#include "Body.h"

void Body::showInfo()
{
    cout << "编号：" << m_ID << "\t"
        << "类型：" << m_Name << "\t"
        << "质量：" << m_Mass << "\t"
        << "坐标：(" << m_X << "," << m_Y << ")\t"
        << "速度：(" << m_Vx << "," << m_Vy << ")\t"
        << "电荷量：" << m_Q << "\t"
        << "初始受力：(" << m_Fx << "," << m_Fy << ")\n";
}