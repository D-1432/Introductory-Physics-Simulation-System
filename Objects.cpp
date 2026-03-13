#include<iostream>
#include<fstream>
#include"Objects.h"
#include"参数控制.h"
#include"Field.h"
#include "Gravity.h"
#include"Magnetic.h"
using namespace std;

Objects::Objects()
{
	//文件不存在：
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);//读文件
	if (!ifs.is_open())
	{
		//测试代码
		//cout << "文件不存在" << endl;


		//初始化人数为零
		this->Obj_Num = 0;
		//初始化数组指针
		this->Obj_Array = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
		//写在构造函数可以保证它总在创建运行时调用，但是缺点是显示的位置不太好

	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//测试代码：
		//cout << "文件为空！" << endl;

		this->Obj_Num = 0;
		//初始化数组指针
		this->Obj_Array = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在且不为空：
	int num = this->get_BodyNum();

	//测试代码
	//cout << "职工人数为： " << num << endl;

	this->Obj_Num = num;
	//开辟空间：
	this->Obj_Array = new Body * [this->Obj_Num];
	//存放已有数据
	this->init_Obj();


	//测试代码
	//for (int i = 0; i < this->Obj_Num; i++)
	//{
	//	cout << "职工编号： " << this->Obj_Array[i]->m_ID
	//		<< "姓名： " << this->Obj_Array[i]->m_Name
	//		<< "部门编号： " << this->Obj_Array[i]->m_DeptID
	//		<< endl;
	//}

}

// 显示菜单函数
void Objects::showMenu()
{
	cout << "****************************" << endl;
	cout << "**  欢迎使用碰撞仿真系统  **" << endl;
	cout << "******  0.退出仿真系统  *****" << endl;
	cout << "******  1.增加物体信息  *****" << endl;
	cout << "******  2.显示物体信息  *****" << endl;
	cout << "******  3.删除多余物体  *****" << endl;
	cout << "******  4.修改物体信息  *****" << endl;
	cout << "******  5.查找物体信息  *****" << endl;
	cout << "******  6.运行仿真系统  *****" << endl;
	cout << "******  7.清空所有文档  *****" << endl;
	


}

//退出系统函数
void Objects::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");

	exit(0);
}

//增加物体函数
void Objects::addObject()
{
	system("cls");
	int addNum = 0;
	cout << "请输入你要增加的物体数量：" << endl;
	cin >> addNum;
	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->Obj_Num + addNum;
		//开辟新空间
		Body** newSpace = new Body * [newSize + 4];
		//拷贝原来数据到新空间下：
		if (this->Obj_Array != NULL)
		{
			for (int i = 0; i < this->Obj_Num; i++)
			{
				newSpace[i] = this->Obj_Array[i];
			}
		}
		//批量添加新物体
		for (int i = 0; i < addNum; i++)
		{
			int a = 0;
			int q = 0;
			int dSelect = 0;
			double m = 0;
			double x = 0;
			double y = 0;
			double vx = 0;
			double vy = 0;
			cout << "请输入第" << i + 1 << "个新物体的编号" << endl;
			cin >> a;
			while (1)
			{
				if (this->IsExist(a) != -1)
				{
					cout << "编号重复，请重新输入" << endl;
					cin >> a;
				}
				else
				{
					break;
				}
			}
			cout << "请输入它的质量 mass = " << endl;
			cin >> m;
			cout << "请输入坐标 \nx = ";
			cin >> x;
			cout << " y = ";
			cin >> y;
			cout << "\n请输入速度 \nvx = ";
			cin >> vx;
			cout << " vy = ";
			cin >> vy;
			cout << "\n请输入带电荷量\nq = ";
			cin >> q;
			Body* body = NULL;
			int P = 1;
			while (P)
			{
				cout << "请选择它的类型：" << endl;
				cout << "1. 粒子\t2.开发中" << endl;
				cin >> dSelect;
				switch (dSelect)
				{
				case 1:
				
					body = new Particle(a, m, x, y, vx, vy, q);
						P = 0;
				
					break;
				default:cout << "开发中，请重新输入！" << endl;
					break;
				}
			}
			newSpace[this->Obj_Num + i] = body;
			system("cls");
		}
		//清理原空间：
		delete[]this->Obj_Array;
		//更改指向新空间：
		this->Obj_Array = newSpace;
		//更新新的物体数量：
		this->Obj_Num = newSize;
		//保存到文件中：
		this->m_FileIsEmpty = false;
		cout << "添加成功！" << endl;
		//保存文件：
		this->save();

	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件函数
void Objects::save()
{
	ofstream ofs;
	ofs.open(FILENAME1, ios::out);
	//循环批量写入：
	for (int i = 0; i < this->Obj_Num; i++)
	{
		ofs << this->Obj_Array[i]->m_ID << "\t"
			<< this->Obj_Array[i]->m_Name << "\t"
			<< this->Obj_Array[i]->m_Mass << "\t"
			<< this->Obj_Array[i]->m_X << "  " << this->Obj_Array[i]->m_Y << "\t"
			<< this->Obj_Array[i]->m_Vx << "  " << this->Obj_Array[i]->m_Vy << "\t"
			<<this->Obj_Array[i]->m_Q
			<< endl;
	}
	ofs.close();
}

//获取物体数量函数
int Objects::get_BodyNum()
{
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);
	int a = 0;
	string name;
	double m = 0;
	double x = 0;
	double y = 0;
	double vx = 0;
	double vy = 0;
	double q = 0;
	int num = 0;
	while (ifs >> a && ifs >> name && ifs >> m && ifs >> x && ifs >> y && ifs >> vx && ifs >> vy && ifs >> q)
	{
		//统计人数
		num++;
	}
	return num;
}

//初始化物体:有历史文件时调用，将其写入数组

void Objects::init_Obj()
{
	ifstream ifs;
	ifs.open(FILENAME1, ios::in);
	int a = 0;
	string name;
	int q = 0;
	double m = 0;
	double x = 0;
	double y = 0;
	double vx = 0;
	double vy = 0;
	int index = 0;

	//这里有代码写的不好，后期开发感觉要变史山；

	while (ifs >> a && ifs >> name && ifs >> m && ifs >> x && ifs >> y && ifs >> vx && ifs >> vy && ifs >> q)
	{
		Body* body = NULL;

		if (name == "粒子")
		{
			body = new Particle(a, m, x, y, vx, vy,q);
		}

		this->Obj_Array[index] = body;
		index++;
	}
	ifs.close();
}

//判断是否出现编号重复：
int Objects::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->Obj_Num; i++)
	{
		if (this->Obj_Array[i]->m_ID == id)
		{
			index = i;

			break;
		}
	}
	return index;
}

//显示物体文件信息：
void Objects::showInformation()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else
	{
		for (int i = 0; i < Obj_Num; i++)
		{
			this->Obj_Array[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除已有物体（按编号）
void Objects::deleteInfo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else
	{
		cout << "输入您要删除的物体编号：" << endl;
		int id = -1;
		cin >> id;
		int index = -1;
		for (int i = 0; i < this->Obj_Num; i++)
		{
			if (this->Obj_Array[i]->m_ID == id)
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			for (int i = index; i < this->Obj_Num; i++)
			{
				this->Obj_Array[i] = this->Obj_Array[i + 1];
			}
			this->Obj_Num--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "未发现编号为：" << id << "的物体，删除失败。" << endl;
		}
	}
	system("pause");
	system("cls");
}

//修改信息函数
void Objects::modInfo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else
	{
		cout << "请输入您要修改的物体编号：" << endl;
		int id = 0;
		cin >> id;
		int index = -1;
		for (int i = 0; i < this->Obj_Num; i++)
		{
			if (this->Obj_Array[i]->m_ID == id)
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			Body* body = NULL;
			int dSelect;
			int a = 0;
			int q = 0;
			double m = 0;
			double x = 0;
			double y = 0;
			double vx = 0;
			double vy = 0;
			cout << "请输入它的新编号：" << endl;
			cin >> a;
			cout << "请输入它的新质量 mass = " << endl;
			cin >> m;
			cout << "请输入坐标 \nx = ";
			cin >> x;
			cout << " y = ";
			cin >> y;
			cout << "\n请输入速度 \nvx = ";
			cin >> vx;
			cout << " vy = ";
			cin >> vy;
			cout << "\n请输入带电荷量\nq = ";
			cin >> q;
			int p = 1;
			while (p)
			{
				cout << "请选择它的类型：" << endl;
				cout << "1. 方块\t 2.开发中" << endl;
				cin >> dSelect;
				switch (dSelect)
				{
				case 1:
					body = new Particle(a, m, x, y, vx, vy,q);
					p = 0;
					break;
				default:
					cout << "输入有误，请重新输入！" << endl;
					break;
				}
			}
			this->Obj_Array[index] = body;
			this->save();
			cout << "修改成功！" << endl;

		}
		else
		{
			cout << "未发现编号为：" << id << "的物体。" << endl;
		}
	}
	system("pause");
	system("cls");
}

//查找物体函数
void Objects::findInfo()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在！" << endl;
	}
	else
	{
		cout << "请输入您要查找的物体编号：" << endl;
		int id = 0;
		cin >> id;
		int index = -1;
		for (int i = 0; i < this->Obj_Num; i++)
		{
			if (this->Obj_Array[i]->m_ID == id)
			{
				index = i;
				break;
			}
		}
		if (index != -1)
		{
			cout << "编号为" << id << "的物体为：" << this->Obj_Array[index]->m_Name << "，质量为：" << this->Obj_Array[index]->m_Mass << "\t"
				<< "坐标为：(" << this->Obj_Array[index]->m_X << "," << this->Obj_Array[index]->m_Y << ")\t"
				<< "速度：Vx = " << this->Obj_Array[index]->m_Vx << ",Vy = " << this->Obj_Array[index]->m_Vy << "\t"
				<< endl;
		}
		else
		{
			cout << "未查找到编号为：" << id << "的物体" << endl;
		}

	}
	system("pause");
	system("cls");
}

//运行仿真函数：
void Objects::Running()
{
	cout << "即将进入仿真系统" << endl;
	system("pause");
	system("cls");
	cout << "请选择您要进行的仿真类型：" << endl
		<< "1.净重力场 2.净磁场" << endl;
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
	{
		Gravity g;
		g.run();
		break;
	}
	case 2:
	{
		Magnetic m;
		m.run();
		break;
	}
	default:
	{
		cout << "开发中，敬请期待！" << endl;
		break;
	}
	}
	

}


Objects::~Objects()
{
	//释放空间
	if (this->Obj_Array != NULL)
	{
		for (int i = 0; i < this->Obj_Num; i++)
		{
			if (this->Obj_Array[i] != NULL)
			{
				delete this->Obj_Array[i];
				this->Obj_Array[i] = NULL;
			}
		}
		delete[]this->Obj_Array;
		this->Obj_Array = NULL;
	}
}