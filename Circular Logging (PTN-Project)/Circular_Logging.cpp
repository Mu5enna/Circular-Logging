#include "Circular_Logging.h"

using namespace std;

void Circular_Logging::startLogCreation() {

}

void Circular_Logging::createLogFile() {
	string logName = currentQuantity + ".log";
}

bool Circular_Logging::manageFileQuantity() {
	int maxQuantity = defineMaxQuantity();
	if (currentQuantity > maxQuantity) {

		return false;
	}
	else {
		return true;
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
