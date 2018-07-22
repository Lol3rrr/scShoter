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

HBITMAP getWindow() {
	windowHWnd = GetForegroundWindow(); // get the Handle for 

	Windhdc = GetWindowDC(windowHWnd); // get the device context of the Window
	hWind = CreateCompatibleDC(Windhdc); // create a device context to use yourself

	 // get the height and width of the screen
	RECT rect;
	GetWindowRect(windowHWnd, &rect);

	// get width and height of window
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	// create a bitmap
	HBITMAP bitmap = CreateCompatibleBitmap(Windhdc, width, height);

	// use the previously created device context with the bitmap
	SelectObject(hWind, bitmap);

	return bitmap;
}

void addToFrames(vector<HBITMAP>* list, HBITMAP bitmap) {

	list->insert(list->begin(), bitmap);

	if (list->size() > framebuffersize) {
		HBITMAP t = list->at(list->size() - 1);
		DeleteObject(t);
		list->pop_back();
	}

}

void VideoCapturer::run() {

	long long millisec;
	chrono::time_point<chrono::steady_clock, chrono::duration<__int64, struct ratio<1, 1000000000> >> start;
	chrono::duration<__int64, struct std::ratio<1, 1000000000>> end;
	int waitTime;

	int timePassedms = 0;

	HBITMAP temp = getWindow();

	while (true) {
		if (!wait) {
			if (timePassedms >= 990) {
				// after the recording is done, release the desktop context you got..
				ReleaseDC(windowHWnd, Windhdc);

				// delete the context you created
				DeleteDC(hWind);

				temp = getWindow();
			}

			start = chrono::high_resolution_clock::now();

			{
				// copy from the desktop device context to the bitmap device context
				BitBlt(hWind, 0, 0, width, height, Windhdc, 0, 0, SRCCOPY);
				addToFrames(&frames, temp);
			}

			end = chrono::high_resolution_clock::now() - start;

			millisec = chrono::duration_cast<chrono::microseconds>(end).count() / 1000;

			waitTime = (1000 / 30) - millisec;
			if (waitTime < 0)
				waitTime = 0;

			timePassedms += waitTime + millisec;

			cout << "Wait time: " << waitTime << endl;

			Sleep(waitTime);
		}
	}

}