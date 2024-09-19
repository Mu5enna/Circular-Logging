#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <fstream>
#include <thread>
#include "nlohmann/json.hpp"

using namespace std;

class Circular_Logging
{
private:
	vector<string> fileNames;
	string logType;
	long waitTime;
	int maxQuantity;
	int freq;
	bool isActive = false;
	void readConfig(const string fileName);
public:
	Circular_Logging(const string fileName) { readConfig(fileName); }
	void startLogCreation();
	void stopLogCreation() { isActive = false; }
	void createLogFile();
	void manageFileQuantity();
	void calcWaitTime();
	string currentTime();
};

