#include<iostream>
#include<fstream>
#include"标头.h"
using namespace std;
int main()
{
	Objects ob;
	int n = 0;
	void plotSimulationResults(const std::string & filePrefix, int numObjects, bool wantAllInOne = true);
	while (true)
	{
		ob.showMenu();
		cout << "请选择你想要的功能：" << endl;
		cin >> n;
		switch (n)
		{
		case 0:ob.exitSystem();
			break;//退出系统
		case 1:ob.addObject();
			break;//添加物体
		case 2:ob.showInformation();
			break;
		case 3:ob.deleteInfo();
			break;//删除物体
		case 4:ob.modInfo();
			break;//修改信息
		case 5:ob.findInfo();
			break;//查找物体
		case 6:ob.Running();
			break;//运行仿真
		case 7:
			break;//初始化系统，删除所有文档
		default:
			break;
		}
	}



	return 0;
}