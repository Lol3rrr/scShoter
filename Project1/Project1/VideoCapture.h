#pragma once
#include <atomic>
#include <vector>
#include <windows.h>

#include "Logger.h"
#include "Utils.h"

using namespace std;

extern atomic<bool> wait;
extern int framesPerSecond;
extern int bufferSize;
extern int framebuffersize;
extern vector<HBITMAP> frames;

class VideoCapturer
{
public:

	VideoCapturer(Logger* pplogger);

	static void run(Logger* plogger, Utils* utils);
	void save(string saveDir, string time);

private:

	Utils utils;
	Logger * logger;

};