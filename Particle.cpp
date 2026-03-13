#include<iostream>
#include"Particle.h"

Particle::Particle(int a, double m, double x0, double y0, double vx0, double vy0,double q)
{
	this->m_Mass = m;
	this->m_X = x0;
	this->m_Y = y0;
	this->m_Vx = vx0;
	this->m_Vy = vy0;
	this->m_ID = a;
	this->m_Name = "粒子";
	this->m_Q = q;
}
void Particle::showInfo()
{
	cout << "物体编号： " << this->m_ID
		<< "\t物体类型： " << this->m_Name
		<< "\t物体质量： " << this->m_Mass
		<< "\t物体坐标： m_X = " << this->m_X << "    m_Y = " << this->m_Y
		<< "\t物体速度： m_Vx = " << this->m_Vx << "    m_Vy = " <<this->m_Vy
		<<"\n物体的带电荷量： m_Q = "<<this->m_Q << endl;
}