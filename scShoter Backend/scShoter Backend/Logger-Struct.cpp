#include "Logger.h"

Logger::Logger(string debugFile, bool debugMode)
{

	debug = debugMode;

	out.open(debugFile);

}

Logger::~Logger()
{

	out.close();

}