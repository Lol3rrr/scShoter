#include "Logger.h"

void Logger::writeDebug(string message) {

	string time = utils.getTime();

	string outputStr = "[Debug] [" + time + "] " + message;

	output << outputStr << endl;

	if (debug) {
		cout << outputStr << endl;
	}

}