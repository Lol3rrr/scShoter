#include "VideoCapture.h"
#include <atlimage.h>
#include <string>
#include "aviFile.h"
#include <iostream>

using namespace std;

void VideoCapturer::save(string saveDir, string time) {

	wait = true;

	Sleep(50);

	vector<HBITMAP> copy = frames;
	vector<HBITMAP>* copyPtr = &copy;

	reverse(copyPtr->begin(), copyPtr->end());

	string save = saveDir + "Video-" + time + ".avi";

	CAviFile* video = new CAviFile(save.c_str(), 0, 30);
	cout << video << endl;

	for (int x = 0; x < copyPtr->size(); x++) {
		if (copyPtr->at(x) != NULL) {
			video->AppendNewFrame(copyPtr->at(x));
		}
	}

	video->~CAviFile();

	cout << "Save Video File" << endl;

	wait = false;
}