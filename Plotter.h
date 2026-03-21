#pragma once
#include <string>
#include <vector>

class Plotter
{
public:
    // 绘制单个物体的轨迹（数据文件格式：t x y vx vy，使用第2,3列绘图）
    static void plotSingle(const std::string& filename, int objectIndex);
    // 在一张图中绘制所有物体
    static void plotAll(const std::vector<std::string>& filenames);
    // 根据文件前缀和物体数量自动绘图
    static void plotSimulationResults(const std::string& filePrefix, int numObjects, bool allInOne = true);
};
