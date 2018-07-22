#include "Logger.h"

void Logger::writeError(string message) {

	string time = utils.getTime();

	string outputStr = "[Error] [" + time + "] " + message;

	output << outputStr << endl;

	if (debug) {
		cout << outputStr << endl;
	}
}