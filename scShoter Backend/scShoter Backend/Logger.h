#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class Logger
{
public:
	Logger(string debugFile, bool debugMode);
	~Logger();

	void writeDebug(string message, string time);

private:

	bool debug;
	ofstream out;

};