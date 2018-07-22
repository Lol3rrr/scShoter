#include "VideoCapture.h"

VideoCapturer::VideoCapturer(Logger* pplogger) {
	logger = pplogger;

	logger->writeDebug("Initializing VideoCapturer...", utils.getTime());

	wait = false;
	framesPerSecond = 30;
	bufferSize = 10;
	framebuffersize = framesPerSecond * bufferSize;
	vector<HBITMAP> temp(framesPerSecond * bufferSize, NULL);
	frames = temp;

	logger->writeDebug("Initialized VideoCapturer", utils.getTime());
}