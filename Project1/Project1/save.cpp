#include "VideoCapture.h"
#include <atlimage.h>
#include <string>
#include "aviFile.h"
#include <iostream>

using namespace std;

void VideoCapturer::save(string saveDir, string time) {

	logger->writeDebug("Started Process for Saving the last Seconds ...", utils.getTime());

	wait = true;

	logger->writeDebug("Set the Waiting Value to true for Process", utils.getTime());

	vector<HBITMAP> copy = frames;
	vector<HBITMAP>* copyPtr = &copy;

	logger->writeDebug("Copied vector of HBitmap successfully", utils.getTime());

	reverse(copyPtr->begin(), copyPtr->end());

	logger->writeDebug("Reversed vector of HBitmap successfully", utils.getTime());

	string save = saveDir + "Video-" + time + ".avi";

	logger->writeDebug("Save Path for the Video has been set to: " + save, utils.getTime());

	CAviFile* video = new CAviFile(save.c_str(), 0, 30);

	for (int x = 0; x < copyPtr->size(); x++) {
		if (copyPtr->at(x) != NULL) {
			video->AppendNewFrame(copyPtr->at(x));
		}
	}

	logger->writeDebug("Added all frames to the Video Object", utils.getTime());

	video->~CAviFile();

	logger->writeDebug("Wrote the Video Object to the File", utils.getTime());

	cout << "Save Video File" << endl;

	wait = false;

	logger->writeDebug("Set the Waiting Value to false again", utils.getTime());
}