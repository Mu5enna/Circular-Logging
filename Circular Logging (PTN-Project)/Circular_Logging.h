#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <fstream>
#include <thread>

using namespace std;

class Circular_Logging
{
private:
	vector<string> fileNames;
	int maxQuantity = 5;
	int freq = 5;
	bool isActive = false;
	void readConfig(const string filePath);
public:
	Circular_Logging(const string filePath) { readConfig(filePath); }
	void startLogCreation();
	void stopLogCreation() { isActive = false; }
	void createLogFile();
	void manageFileQuantity();
	string currentTime();
};

