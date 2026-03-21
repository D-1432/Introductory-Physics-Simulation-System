#include <iostream>
#include <limits>
#include "Constants.h"
#include "BodyManager.h"
#include "Simulation.h"
#include "Plotter.h"
#include "GravityField.h"
#include "MagneticField.h"
#include "ElectricField.h"

using namespace std;

void showMenu()
{
    cout << "****************************" << endl;
    cout << "**  欢迎使用碰撞仿真系统  **" << endl;
    cout << "******  0.退出仿真系统  *****" << endl;
    cout << "******  1.增加物体信息  *****" << endl;
    cout << "******  2.显示物体信息  *****" << endl;
    cout << "******  3.删除物体信息  *****" << endl;
    cout << "******  4.修改物体信息  *****" << endl;
    cout << "******  5.查找物体信息  *****" << endl;
    cout << "******  6.运行仿真系统  *****" << endl;
    cout << "******  7.清空所有文档  *****" << endl;
}

int main()
{
    BodyManager manager;
    manager.loadFromFile(FILENAME1);

    int choice;
    while (true) {
        showMenu();
        cout << "请选择功能: ";
        cin >> choice;

        switch (choice) {
        case 0:
            cout << "感谢使用，再见！" << endl;
            return 0;

        case 1:
            manager.addObject();
            break;

        case 2:
            manager.showAll();
            system("pause");
            system("cls");
            break;

        case 3: {
            int id;
            cout << "输入要删除的物体编号: ";
            cin >> id;
            if (manager.removeObject(id))
                cout << "删除成功！" << endl;
            else
                cout << "未找到编号为 " << id << " 的物体。" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 4: {
            int id;
            cout << "输入要修改的物体编号: ";
            cin >> id;
            if (manager.modifyObject(id))
                cout << "修改成功！" << endl;
            else
                cout << "未找到编号为 " << id << " 的物体。" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 5: {
            int id;
            cout << "输入要查找的物体编号: ";
            cin >> id;
            if (manager.findAndShow(id))
                ;
            else
                cout << "未找到编号为 " << id << " 的物体。" << endl;
            system("pause");
            system("cls");
            break;
        }

        case 6: {
            // 仿真设置
            int steps;
            cout << "请输入仿真步数: ";
            cin >> steps;

            Simulation sim(DT);

            // 选择物理场
            int gChoice, bChoice, eChoice;
            cout << "是否添加重力场？(1:是 2:否): ";
            cin >> gChoice;
            if (gChoice == 1) {
                sim.addField(new GravityField(G));
            }

            cout << "是否添加磁场？(1:是 2:否): ";
            cin >> bChoice;
            if (bChoice == 1) {
                double B;
                cout << "请输入磁场强度 B: ";
                cin >> B;
                sim.addField(new MagneticField(B));
            }

            cout << "是否添加电场？(1:是 2:否): ";
            cin >> eChoice;
            if (eChoice == 1) {
                double Ex, Ey;
                cout << "请输入电场强度 Ex: ";
                cin >> Ex;
                cout << "请输入电场强度 Ey: ";
                cin >> Ey;
                sim.addField(new ElectricField(Ex, Ey));
            }

            // 获取物体列表
            auto bodies = manager.getBodies();
            if (bodies.empty()) {
                cout << "没有物体可仿真，请先添加物体。" << endl;
            }
            else {
                sim.setBodies(bodies);
                sim.run(steps, "run_");

                // 绘图
                int plotChoice;
                cout << "是否需要制图？(1:是 2:否): ";
                cin >> plotChoice;
                if (plotChoice == 1) {
                    Plotter::plotSimulationResults("run_", bodies.size(), true);
                }
            }
            system("pause");
            system("cls");
            break;
        }

        case 7: {
            // 清空所有文档：删除文件，清空内存
            remove(FILENAME1);
            manager.loadFromFile(FILENAME1);  // 重新加载（变为空）
            cout << "所有物体已清空。" << endl;
            system("pause");
            system("cls");
            break;
        }

        default:
            cout << "无效选项，请重新输入。" << endl;
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}