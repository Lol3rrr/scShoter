#pragma once
#include <shlobj.h>
#include <windows.h>
#include <string>
#include <ctime>

#include "Logger.h"

using namespace std;

class Utils
{
public:

	void getDesktopPath(char* array);
	string getTime();
	bool DirExists(string path);
	
	HBITMAP getBitmap(HWND window, int monitorCount, Logger* plogger);

private:

};