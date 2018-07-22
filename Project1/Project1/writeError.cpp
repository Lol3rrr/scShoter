#include "Logger.h"

void Logger::writeError(string message, string time) {

	string outputStr = "[Error] [" + time + "] " + message;

	output << outputStr << endl;

	if (debug) {
		cout << outputStr << endl;
	}
}