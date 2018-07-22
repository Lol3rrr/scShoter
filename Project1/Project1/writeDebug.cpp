#include "Logger.h"

void Logger::writeDebug(string message, string time) {

	string outputStr = "[Debug] [" + time + "] " + message;

	output << outputStr << endl;

	if (debug) {
		cout << outputStr << endl;
	}

}