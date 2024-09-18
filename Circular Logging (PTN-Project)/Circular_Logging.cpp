#include "Circular_Logging.h"

using namespace std;

void Circular_Logging::readConfig(string filePath) {

}

void Circular_Logging::startLogCreation() {
	filesystem::path directoryPath = "Logs";
	if (filesystem::exists(directoryPath) && filesystem::is_directory(directoryPath)) {
		for (const auto& entry : filesystem::directory_iterator(directoryPath)) {
			string fileName = entry.path().string();
			fileNames.push_back(fileName);
		}
	}
	for (int i = 0; i < 10; i++) {
		createLogFile();
		this_thread::sleep_for(chrono::seconds(freq));
	}
}

void Circular_Logging::createLogFile() {
	string strTime = currentTime();
	string logFileName = strTime + ".log";
	filesystem::path directoryPath = "Logs";
	if (!exists(directoryPath)) {
		create_directory(directoryPath);
	}

	string strFilePath = "Logs/" + logFileName;
	filesystem::path filePath = strFilePath;
	ofstream logFile(filePath);
	if (logFile.is_open()) {
		logFile << "Log created at " + strTime;
		logFile.close();
		fileNames.push_back(strFilePath);
	}
	manageFileQuantity();
}

void Circular_Logging::manageFileQuantity() {
	while (fileNames.size() > maxQuantity) {
		filesystem::path oldestFile = fileNames.front();
		filesystem::remove(oldestFile);
		fileNames.erase(fileNames.begin());
	}
}

string Circular_Logging::currentTime() {
	auto now = chrono::system_clock::now();
	time_t crntTime = chrono::system_clock::to_time_t(now);
	tm tmTime;
	gmtime_s(&tmTime, &crntTime);
	char timeArry[100];
	strftime(timeArry, sizeof(timeArry), "%Y-%m-%d_%H-%M-%S", &tmTime);
	string strTime = string(timeArry);
	return strTime;
}
