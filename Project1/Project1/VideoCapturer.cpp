#include "VideoCapture.h"

VideoCapturer::VideoCapturer(Logger* plogger) {
	logger = plogger;

	wait = false;
	framesPerSecond = 30;
	bufferSize = 10;
	framebuffersize = framesPerSecond * bufferSize;
	vector<HBITMAP> temp(framesPerSecond * bufferSize, NULL);
	frames = temp;
}