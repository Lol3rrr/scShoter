#pragma once
#include <atomic>
#include <vector>
#include <windows.h>

#include "Logger.h"

using namespace std;

extern atomic<bool> wait;
extern int framesPerSecond;
extern int bufferSize;
extern int framebuffersize;
extern vector<HBITMAP> frames;

class VideoCapturer
{
public:

	VideoCapturer(Logger* plogger);

	static void run();
	void save(string saveDir, string time);

private:

	Logger * logger;

};