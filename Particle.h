#pragma once
#include"Body.h"

class Particle :public Body
{
public:
	//构造函数，实例化类对象
	Particle(int a, double m, double x0, double y0, double vx0, double vy0,double q,double fx,double fy);
	void showInfo();
};