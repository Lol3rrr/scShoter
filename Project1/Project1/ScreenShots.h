#pragma once
#include <windows.h>
#include <atlimage.h>
#include <string>
#include <iostream>

#include "Utils.h"
#include "Logger.h"

using namespace std;

class ScreenShots
{
public:

	ScreenShots(string savePath, int monitorAmount, Logger* plogger);

	void takeDesktopScreenshot(bool debug);
	void takeFocusedScreenshot(bool debug);

private:

	Utils utils;
	Logger* logger;

	string saveDir;
	int monitorCount;

};