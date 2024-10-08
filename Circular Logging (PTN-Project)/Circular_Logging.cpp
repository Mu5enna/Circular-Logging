#include "Circular_Logging.h"

using namespace std;

void Circular_Logging::readConfig(string fileName) {
	// Reading JSON file and transfer values using nlohmann/json library
	ifstream jsonFile("variables.json");
	nlohmann::json j;
	jsonFile >> j;

	freq = j["Frequency"];
	maxQuantity = j["MaxQuantity"];
	logType = j["LogType"];
	repeatTime = j["AmountofRepeat"];
	calcWaitTime();
}

// Calculating wait time in seconds according to LogType and Frequency given in JSON file
void Circular_Logging::calcWaitTime() {
	
	if (logType == "Minute") {
		waitTime = freq * 60;
	}
	else if (logType == "Hour") {
		waitTime = freq * 3600;
	}
	else if (logType == "Day") {
		waitTime = freq * 86400;
	}
	//If log type is second or not valid
	else {
		waitTime = freq;
	}
}

void Circular_Logging::startLogCreation() {
	filesystem::path directoryPath = "Logs";
	// Loading previous log files in directory
	if (filesystem::exists(directoryPath) && filesystem::is_directory(directoryPath)) {
		for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
			string fileName = entry.path().string();
			fileNames.push_back(fileName);
		}
	}
	for (int i = 0; i <= repeatTime; i++) {
		if (repeatTime <= 0) {
			--i;
		}
		if (i == repeatTime) {
			continue;
		}
		createLogFile();
		this_thread::sleep_for(chrono::seconds(waitTime));
	}
}

void Circular_Logging::createLogFile() {
	string strTime = currentTime();
	string logFileName = strTime + ".log";
	filesystem::path directoryPath = "Logs";
	// Checking if directory exists and creates if it doesn't
	if (!exists(directoryPath)) {
		create_directory(directoryPath);
	}

	string strFilePath = "Logs/" + logFileName;
	filesystem::path filePath = strFilePath;
	ofstream logFile(filePath);
	if (logFile.is_open()) {
		logFile << "Log created at " + strTime;
		logFile.close();
		// Adding file path to the list to remove when it is necessary
		fileNames.push_back(strFilePath);
	}
	manageFileQuantity();
}

void Circular_Logging::manageFileQuantity() {
	// Checks if stored file amount is greater than the MaxQuantity given in JSON file
	while (fileNames.size() > maxQuantity) {
		// Finding the oldest log file and removing it from list and directory
		filesystem::path oldestFile = fileNames.front();
		filesystem::remove(oldestFile);
		fileNames.erase(fileNames.begin());
	}
}

string Circular_Logging::currentTime() {
	// Declaring current time and converting it to a string in a UTC format
	auto now = chrono::system_clock::now();
	time_t crntTime = chrono::system_clock::to_time_t(now);
	tm tmTime;
	gmtime_s(&tmTime, &crntTime);
	char timeArry[100];
	strftime(timeArry, sizeof(timeArry), "%Y-%m-%d_%H-%M-%S", &tmTime);
	string strTime = string(timeArry);
	return strTime;
}
