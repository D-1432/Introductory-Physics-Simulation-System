#pragma once
#include"Body.h"
#include"Particle.h"
class Objects
{
public:
	//物体数量
	int Obj_Num;
	//维护物体数组的地址的指针
	Body** Obj_Array;
	//判断文件是否为空
	bool m_FileIsEmpty;
	//构造函数
	Objects();
	//增加物体函数
	void addObject();
	//保存文件
	void save();
	//获取数量
	int get_BodyNum();
	//初始化物体:读取历史文件
	void init_Obj();
	//判断是否编号重复,返回值设置为 int 是为了后续可以用它查找获取指定物体
	int IsExist(int id);
	//显示菜单函数
	void showMenu();
	//退出系统函数
	void exitSystem();
	//显示物体信息函数
	void showInformation();
	//删除物体信息函数
	void deleteInfo();
	//修改物体信息函数
	void modInfo();
	//查找物体并显示函数
	void findInfo();
	//运行仿真函数
	void Running();
	~Objects();
};