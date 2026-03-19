#include"Magnetic.h"
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>
Magnetic::Magnetic()
{
	num = this->get_BodyNum();
	cout << "请设置磁场强度 B " << endl
		<< "= ";
	cin >> B;
}
