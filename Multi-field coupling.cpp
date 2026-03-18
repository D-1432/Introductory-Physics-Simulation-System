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
		double c = atan2(vy , vx);
		sprintf_s(filename, "run_%d.txt", i);
		ofstream ofs(filename);
		ofs << "#" << "t" << setw(15) << "x" << setw(15) << "y" << setw(15) << "vx" << setw(15) << "vy" << endl;
		for (int j = 1; j <= step; j++)
		{
			ofs << (DT * (j - 1)) << setw(15) << x << setw(15) << y << setw(15) << vx << setw(15) << vy << endl;
			if (B_select == 1 && G_select == 1) {
				// 磁场和重力场耦合：使用 Boris 方法（二阶精度）
				double half_dt = 0.5 * DT;

				// 半重力加速度（假设重力方向为 +y，与原始代码一致）
				vy += G * half_dt;

				// 磁场旋转：速度矢量绕垂直于平面的轴旋转角度 w*DT
				double theta = w * DT;
				double vx_new = vx * cos(theta) - vy * sin(theta);
				double vy_new = vx * sin(theta) + vy * cos(theta);
				vx = vx_new;
				vy = vy_new;

				// 另半重力加速度
				vy += G * half_dt;

				// 更新位置（使用新速度）
				x += vx * DT;
				y += vy * DT;
			}
			else if (B_select == 1) {
				// 仅有磁场：速度旋转，位置用新速度更新
				double theta = w * DT;
				double vx_new = vx * cos(theta) - vy * sin(theta);
				double vy_new = vx * sin(theta) + vy * cos(theta);
				vx = vx_new;
				vy = vy_new;
				x += vx * DT;
				y += vy * DT;
			}
			else if (G_select == 1) {
				// 仅有重力：匀加速运动（原始公式不变）
				x += vx * DT;
				y += vy * DT + 0.5 * G * DT * DT;
				vy += G * DT;
				// vx 保持不变
			}
			else {
				// 无场：匀速直线运动
				x += vx * DT;
				y += vy * DT;
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