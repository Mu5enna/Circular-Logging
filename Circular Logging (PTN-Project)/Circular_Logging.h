#pragma once

#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <fstream>

class Circular_Logging
{
private:
	vector<string> fileNames;
	int maxQuantity;
	int freq;
	bool isActive = false;
	void readConfig(const string filePath);
public:
	Circular_Logging(const string filePath) { readConfig(filePath); }
	void startLogCreation();
	void stopLogCreation() { isActive = false; }
	void createLogFile();
	bool manageFileQuantity();
	string currentTime();
};

