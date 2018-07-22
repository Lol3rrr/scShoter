#pragma once

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class Logger
{
public:

	Logger(string dataFolder, bool debugMode);
	~Logger();

	void writeDebug(string message, string time);
	void writeError(string message, string time);
	void writeNormal(string message, string time);

private:

	bool debug;
	ofstream output;

};