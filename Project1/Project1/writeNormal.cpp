#include "Logger.h"

void Logger::writeNormal(string message) {

	string time = utils.getTime();

	string outputStr = "[" + time + "] " + message;

	output << outputStr << endl;

	if (debug) {
		cout << outputStr << endl;
	}

}