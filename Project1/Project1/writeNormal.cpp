#include "Logger.h"

void Logger::writeNormal(string message, string time) {

	string outputStr = "[" + time + "] " + message;

	output << outputStr << endl;

	if (debug) {
		cout << outputStr << endl;
	}

}