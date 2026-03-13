#pragma once
#include"Objects.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   // system()
#include <vector>
class  Field :public Objects
{
public:
	int num = 0;
	double m = 0;
	double x = 0, y = 0, vx = 0, vy = 0;
	double q = 0;
	double B = 0;
	Field();
	void plotSingleObject(const std::string& filename, int objectIndex);
	void plotAllObjects(const std::vector<std::string>& filenames);
	void plotSimulationResults(const std::string& filePrefix, int numObjects, bool wantAllInOne = true);
	~Field();
};