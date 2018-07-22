#include <chrono>
#include <shlobj.h>
#include <string>
#include <atlimage.h>
#include <iostream>

#include "VideoCapture.h"

int width;
int height;

HWND windowHWnd;
HDC Windhdc;
HDC hWind;

atomic<bool> wait;
int framesPerSecond;
int bufferSize;
int framebuffersize;
vector<HBITMAP> frames;

HBITMAP getWindow(Logger* plogger, Utils* utils) {
	windowHWnd = GetForegroundWindow(); // get the Handle for 

	plogger->writeDebug("Successfully got the Focused Window", utils->getTime());

	Windhdc = GetWindowDC(windowHWnd); // get the device context of the Window
	hWind = CreateCompatibleDC(Windhdc); // create a device context to use yourself

	plogger->writeDebug("Successfully got the Device Context for the Window", utils->getTime());

	 // get the height and width of the screen
	RECT rect;
	GetWindowRect(windowHWnd, &rect);

	// get width and height of window
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	plogger->writeDebug("Successfully got the Size of the Window", utils->getTime());

	// create a bitmap
	HBITMAP bitmap = CreateCompatibleBitmap(Windhdc, width, height);

	// use the previously created device context with the bitmap
	SelectObject(hWind, bitmap);

	plogger->writeDebug("Successfully bound the new Device Context to the Bitmap", utils->getTime());

	return bitmap;
}

void addToFrames(vector<HBITMAP>* list, HBITMAP bitmap, Logger* plogger, Utils* utils) {

	list->insert(list->begin(), bitmap);

	plogger->writeDebug("Successfully added HBitmap to the beginning of the vector", utils->getTime());

	if (list->size() > framebuffersize) {
		HBITMAP t = list->at(list->size() - 1);
		DeleteObject(t);
		list->pop_back();
		
		plogger->writeDebug("Successfully deleted last HBitmap Object in the vector", utils->getTime());
	}

}

void VideoCapturer::run(Logger* plogger, Utils* utils) {

	plogger->writeDebug("Started Process to Record the last Seconds", utils->getTime());

	long long millisec;
	chrono::time_point<chrono::steady_clock, chrono::duration<__int64, struct ratio<1, 1000000000> >> start;
	chrono::duration<__int64, struct std::ratio<1, 1000000000>> end;
	int waitTime;

	int timePassedms = 0;
	int iterations = 0;
	int overallTimeWaited = 0;

	HBITMAP temp = getWindow(plogger, utils);

	while (true) {
		if (!wait) {
			if (timePassedms >= 990) {
				// after the recording is done, release the desktop context you got..
				ReleaseDC(windowHWnd, Windhdc);

				// delete the context you created
				DeleteDC(hWind);

				plogger->writeDebug("Successfully deleted the last Context and Released the Others", utils->getTime());

				temp = getWindow(plogger, utils);

				plogger->writeDebug("Successfully refreshed the Window", utils->getTime());
			}

			start = chrono::high_resolution_clock::now();

			{
				// copy from the desktop device context to the bitmap device context
				BitBlt(hWind, 0, 0, width, height, Windhdc, 0, 0, SRCCOPY);
				addToFrames(&frames, temp, plogger, utils);

				plogger->writeDebug("Added loaded HBitmap to the list of HBitmaps", utils->getTime());
			}

			end = chrono::high_resolution_clock::now() - start;

			millisec = chrono::duration_cast<chrono::microseconds>(end).count() / 1000;

			waitTime = (1000 / 30) - millisec;
			if (waitTime < 0)
				waitTime = 0;

			timePassedms += waitTime + millisec;
			overallTimeWaited += waitTime;
			iterations++;

			if (iterations = framesPerSecond * 3) {
				double averageWait = (double)overallTimeWaited / (double)iterations;
				plogger->writeDebug("Average Waiting time: " + to_string(averageWait), utils->getTime());

				overallTimeWaited = 0;
				iterations = 0;
			}

			Sleep(waitTime);
		}
	}

}