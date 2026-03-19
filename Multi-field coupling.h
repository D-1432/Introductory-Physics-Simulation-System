#pragma once
#include"Gravity.h"
#include"Magnetic.h"
class  coupling :public Field
{
public:
	int G_select = 0;
	int B_select = 0;
	int E_select = 0;
	coupling();
	void runing();


};
