#pragma once

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>

#include "Logger.h"

using namespace std;

class Main
{
public:
	Main();
	~Main();

	void start();

private:

	void startSocket();

	Logger* logger;
	thread* socketThread;

};