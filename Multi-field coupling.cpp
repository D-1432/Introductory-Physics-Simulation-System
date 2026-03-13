#include"Multi-field coupling.h"
#include<iostream>
#include<iomanip>
using namespace std;

coupling::coupling()
{
	num = this->get_BodyNum();
	cout << "请选择要添加的物理场：\n"
		<< "是否添加重力场？（默认G = 9.8）\n1.添加\t2.不添加\n";
	cin >> G_select;
	cout << "是否添加磁场？\n1.添加\t2.不添加\n";
	cin >> B_select;
	if (B_select == 1)
	{
		cout << "请设置磁场强度 B " << endl
			<< "= ";
		cin >> B;
	}
}
void coupling::runing()
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
		sprintf_s(filename, "run_%d.txt", i);
		ofstream ofs(filename);
		ofs << "#" << "t" << setw(15) << "x" << setw(15) << "y" << setw(15) << "vx" << setw(15) << "vy" << endl;
		for (int j = 1; j <= step; j++)
		{
			ofs << (DT * (j - 1)) << setw(15) << x << setw(15) << y << setw(15) << vx << setw(15) << vy << endl;
			if (B_select == 1)
			{
				x = vx * DT + x;
				y = vy * DT + y;
				vx = v * cos(c + w * DT * j);
				vy = v * sin(c + w * DT * j);
			}
			if (G_select == 1)
			{
				x = (x + vx * DT);
				y = (y + vy * DT + 0.5 * G * DT * DT);
				vx = vx;
				vy = (vy + G * DT);
			}


		}
		ofs.close();

	}
	cout << "仿真完成，数据以保存到 run_n.txt 系列文件" << endl;
	int p = 0;
	cout << "是否需要制图？\n1.需要\t2.不需要" << endl;
	cin >> p;
	if (p == 1)
	{
		plotSimulationResults("run_", num, true);
	}
	system("pause");
	system("cls");
}