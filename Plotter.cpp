#include "Plotter.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

void Plotter::plotSingle(const string& filename, int objectIndex)
{
    string scriptName = "plot_temp.gp";
    ofstream script(scriptName);
    if (!script.is_open()) {
        cerr << "无法创建临时脚本文件！" << endl;
        return;
    }

    script << "set title 'Object " << objectIndex << " trajectory'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
    script << "plot '" << filename << "' using 2:3 with lines title 'Object " << objectIndex << "'\n";
    script << "pause -1 'Press Enter to close...'\n";
    script.close();

    string command = "gnuplot -persist " + scriptName;
    int ret = system(command.c_str());
    if (ret != 0) {
        cerr << "调用 Gnuplot 失败，请检查是否已安装 Gnuplot 并加入 PATH。" << endl;
    }
}

void Plotter::plotAll(const vector<string>& filenames)
{
    if (filenames.empty()) return;

    string scriptName = "plot_all_temp.gp";
    ofstream script(scriptName);
    if (!script.is_open()) {
        cerr << "无法创建临时脚本文件！" << endl;
        return;
    }

    script << "set title 'All Objects Trajectories'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
    script << "plot ";
    for (size_t i = 0; i < filenames.size(); ++i) {
        script << "'" << filenames[i] << "' using 2:3 with lines title 'Object " << i << "'";
        if (i != filenames.size() - 1)
            script << ", ";
    }
    script << "\n";
    script << "pause -1 'Press Enter to close...'\n";
    script.close();

    string command = "gnuplot -persist " + scriptName;
    system(command.c_str());
}

void Plotter::plotSimulationResults(const string& filePrefix, int numObjects, bool allInOne)
{
    vector<string> filenames;
    for (int i = 0; i < numObjects; ++i) {
        string filename = filePrefix + to_string(i) + ".txt";
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

    if (allInOne) {
        plotAll(filenames);
    }
    else {
        for (size_t i = 0; i < filenames.size(); ++i) {
            plotSingle(filenames[i], i);
        }
    }
}