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
#include <fstream>

using namespace std;

class FileUploadInterface
{
public:

	FileUploadInterface(uint Serverport);

	void start();

private:

	void createSocket(uint port);
	void listening();
	void processData();

	uint port;
	int serverSocket;

};