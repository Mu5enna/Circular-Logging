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
	// Vector to store existing log files names
	vector<string> fileNames;
	// Changable variables from JSON file
	string logType;
	int maxQuantity;
	int freq;
	int repeatTime;
	// Amount of time program waits between creating logs
	long waitTime;
	// Function to read JSON file and transfer values
	void readConfig(const string fileName);
	// Function to create log files
	void createLogFile();
	// Function to control the maximum amount of log files stored
	void manageFileQuantity();
	// Function to calculate waitTime
	void calcWaitTime();
	// Function to determine and return the current time in UTC as string
	string currentTime();
public:
	Circular_Logging(const string fileName) { readConfig(fileName); }
	// Function to start and control the log creating process
	void startLogCreation();
};

