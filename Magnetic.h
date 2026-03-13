#pragma once
#include"²ÎÊı¿ØÖÆ.h"
#include"Field.h"

class Magnetic :public Field
{
public:
	double B = 0;
	Magnetic();
	void run();
};