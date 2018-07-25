#pragma once

#include <string>

#include "Utils.h"

using namespace std;

class Networking
{
public:
	Networking();
	~Networking();

	void sendFile(string imagePath, string fileName);

private:

	string ip = "";
	string port = "";

	Utils utils;

};