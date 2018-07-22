#pragma once

#include <string>
#include <fstream>

#include "Utils.h"
#include "Settings.h"

using namespace std;

class Logger
{
public:

	Logger(string dataFolder, bool debugMode);
	~Logger();

	void writeDebug(string message);
	void writeError(string message);
	void writeNormal(string message);

private:

	Utils utils;

	bool debug;
	ofstream output;

};