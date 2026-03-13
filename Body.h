#pragma once
#include<iostream>
using namespace std;
class Body
{
public:
	//质量
	double m_Mass = 0;

	//坐标
	double m_X = 0;
	double m_Y = 0;

	//速度
	double m_Vx = 0;
	double m_Vy = 0;

	//编号
	int m_ID = 0;

	//类名
	string m_Name = " ";

	//特殊物理属性
	double m_Q = 0;

	//显示函数
	virtual void showInfo();
};