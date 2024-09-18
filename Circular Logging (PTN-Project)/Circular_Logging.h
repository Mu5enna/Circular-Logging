#pragma once

#include <string>
#include <chrono>

class Circular_Logging
{
private:
	int currentQuantity;
	bool isActive = false;
public:
	void startLogCreation();
	void stopLogCreation() { isActive = false; }
	void createLogFile();
	bool manageFileQuantity();
	int defineFrequency();
	int defineMaxQuantity();
	string currentTime();
};

