#pragma once

#include <string>

#include "Utils.h"
#include "Logger.h"

using namespace std;

class Networking
{
public:
	Networking(Logger* plogger, int buffersize);
	~Networking();

	void sendFile(string imagePath, string fileName);

private:

	string ip = "";
	string port = "";
	int bufferSize = 0;

	Utils utils;
	Logger* logger;

};