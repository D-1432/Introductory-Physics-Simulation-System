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
void Magnetic::run()
{
	cout << "请输入您想运行的步数 step = " << endl;
	int step = 0;
	cin >> step;
	char filename[265];
	for (int i = 0; i < num; i++)
	{
		m = Obj_Array[i]->m_Mass;
		x = Obj_Array[i]->m_X;
		y = Obj_Array[i]->m_Y;
		vx = Obj_Array[i]->m_Vx;
		vy = Obj_Array[i]->m_Vy;
		q = Obj_Array[i]->m_Q;
		double v = sqrt((vx * vx + vy * vy));
		double r = ((m * v) / (q * B));
		double w = v / r;
		double c = atan(vy / vx);
		sprintf_s(filename, "B_run_%d.txt", i);
		ofstream ofs(filename);
		ofs << "#" << "t" << setw(15) << "x" << setw(15) << "y" << setw(15) << "vx" << setw(15) << "vy" << endl;
		for (int j = 1; j <= step; j++)
		{
			ofs << (DT * (j - 1)) << setw(15) << x << setw(15) << y << setw(15) << vx << setw(15) << vy << endl;
			x = vx * DT + x;
			y = vy * DT + y;
			vx = v * cos(c + w * DT*j);
			vy = v * sin(c + w * DT*j);
			

		}
		ofs.close();

	}
	cout << "仿真完成，数据以保存到 B_run_n.txt 系列文件" << endl;
	int p = 0;
	cout << "是否需要制图？\n1.需要\t2.不需要" << endl;
	cin >> p;
	if (p == 1)
	{
		plotSimulationResults("B_run_", num, true);
	}
	system("pause");
	system("cls");
}