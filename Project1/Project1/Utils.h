#pragma once
#include <shlobj.h>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;

class Utils
{
public:

	void getDesktopPath(char* array);
	string getTime();
	bool DirExists(string path);

private:

};