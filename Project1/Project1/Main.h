#pragma once
#include <string>
#include <Windows.h>
#include <atomic>
#include <iostream>
#include <thread>

#include "Utils.h"
#include "ScreenShots.h"
#include "Settings.h"
#include "VideoCapture.h"
#include "Logger.h"

using namespace std;

class Main
{
public:

	Main();
	~Main();

	static const int Version = 001000;

	void start();
	void openConsole();

	ScreenShots* screenshots;
	Settings* settings;
	Logger* logger;
	Utils* utils;
	VideoCapturer* capturer;
	atomic<bool> console;
	atomic<bool> settingsMenu;

private:

	void setupHotKeys();
	bool filterCommand(string command);
	void writeHelp();
	void startCapturer();

};