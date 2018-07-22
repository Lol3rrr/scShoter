#include "Logger.h"

Logger::Logger(string dataFolder, bool debugMode)
{
	debug = debugMode;

	char* appdata = nullptr;
	size_t sz = 0;
	_dupenv_s(&appdata, &sz, "APPDATA");

	string loggerFile = string(appdata) + "\\" + dataFolder + "\\debug.log";

	output.open(loggerFile);

}

Logger::~Logger()
{

	output.close();

}