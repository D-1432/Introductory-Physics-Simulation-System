#include<iostream>
#include"Body.h"

void Body::showInfo()
{
	cout << "编号为：" << this->m_ID << "\t"
		<< "类型为：" << this->m_Name << "\t"
		<< "坐标为：(" << this->m_X << "," << this->m_Y << ")\t"
		<< "速度为：(" << this->m_Vx << "," << this->m_Vy << ")\t";
}