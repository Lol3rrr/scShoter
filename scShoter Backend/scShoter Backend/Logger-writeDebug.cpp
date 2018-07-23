#include "Logger.h"

void Logger::writeDebug(string message, string time) {

	string outStr = "[Debug]";

	if (debug) {
		cout << outStr << endl;
	}

	out.write(outStr.c_str(), outStr.length());

}