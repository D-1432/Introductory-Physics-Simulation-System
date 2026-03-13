#include"Field.h"
Field::Field()
{

}
// PlotUtils.cpp
// 功能：读取仿真输出文件（如 B_run_n.txt），调用 Gnuplot 绘制 x-y 轨迹
// 使用前请确保系统已安装 Gnuplot 并已将 gnuplot 添加到环境变量 PATH 中

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   // system()
#include <vector>
using namespace std;
// 绘制单个物体的轨迹，数据文件格式：第一行为注释，之后每列为 t x y vx vy
void Field::plotSingleObject(const string& filename, int objectIndex) 
{
    // 创建临时 gnuplot 脚本文件
    string scriptName = "plot_temp.gp";
    ofstream script(scriptName);
    if (!script.is_open()) {
        cerr << "无法创建临时脚本文件！" << endl;
        return;
    }

    // 写入 gnuplot 命令
    script << "set title 'Object " << objectIndex << " trajectory'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
 /*   if (this->B != 0)
    {
        script << "set size ratio -1\n";
    }*/
    script << "plot '" << filename << "' using 2:3 with lines title 'Object " << objectIndex << "'\n";
    script << "pause -1 'Press Enter to close...'\n";   // 等待用户按键后关闭窗口
    script.close();

    // 调用 gnuplot 执行脚本
    string command = "gnuplot -persist " + scriptName;
    int ret = system(command.c_str());
    if (ret != 0) {
        cerr << "调用 Gnuplot 失败，请检查是否已安装 Gnuplot 并加入 PATH。" << endl;
    }

    // 删除临时脚本文件（可选）
    // remove(scriptName.c_str());
}

// 绘制所有物体的轨迹（同一张图中）
void Field::plotAllObjects(const vector<string>& filenames) {
    string scriptName = "plot_all_temp.gp";
    ofstream script(scriptName);
    if (!script.is_open()) {
        cerr << "无法创建临时脚本文件！" << endl;
        return;
    }

    script << "set title 'All Objects Trajectories'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
 /*   if (this->B != 0)
    {
        script << "set size ratio -1\n";
    }*/
    script << "plot ";
    for (size_t i = 0; i < filenames.size(); ++i) {
        script << "'" << filenames[i] << "' using 2:3 with lines title 'Object " << i << "'";
        if (i != filenames.size() - 1)
            script << ", ";
    }
    script << "\n";
    script << "pause -1 'Press Enter to close...'\n";
    script.close();

    std::string command = "gnuplot -persist " + scriptName;
    int ret = system(command.c_str());
    if (ret != 0) {
        cerr << "调用 Gnuplot 失败，请检查是否已安装 Gnuplot 并加入 PATH。" << endl;
    }
    // remove(scriptName.c_str());
}

// 对外提供的函数：根据物体数量 num 和文件前缀（如 "B_run_"）自动生成文件名并绘图
// 若 wantAllInOne 为 true，则所有物体轨迹绘制在同一张图中，否则为每个物体单独绘制
void Field::plotSimulationResults(const string& filePrefix, int numObjects, bool wantAllInOne ) 
{
    vector<string> filenames;
    for (int i = 0; i < numObjects; ++i) {
        string filename = filePrefix + to_string(i) + ".txt";
        // 检查文件是否存在
        ifstream f(filename.c_str());
        if (f.good()) {
            filenames.push_back(filename);
        }
        else {
            cerr << "警告：文件 " << filename << " 不存在，已跳过。" << endl;
        }
    }

    if (filenames.empty()) {
        cerr << "没有找到任何有效的数据文件！" << endl;
        return;
    }

    if (wantAllInOne) {
        plotAllObjects(filenames);
    }
    else {
        for (size_t i = 0; i < filenames.size(); ++i) {
            plotSingleObject(filenames[i], i);
        }
    }
}
Field::~Field()
{

}