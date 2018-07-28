#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <thread>
#include <fstream>

#include "Logger.h"
#include "FileUploadInterface.h"

using namespace std;

class Main
{
public:
	Main();
	~Main();

	void start();

	const int uploadPort = 23510;

private:

	void startSocket();

	
	Logger* logger;
	thread* socketThread;
	FileUploadInterface* fileUploadInterface;

};