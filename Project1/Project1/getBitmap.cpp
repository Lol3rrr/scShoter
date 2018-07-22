#include "Utils.h"

HBITMAP Utils::getBitmap(HWND window, int monitorCount, Logger* plogger) {

	HDC Deskhdc = GetDC(window); // get the desktop device context
	HDC hDesk = CreateCompatibleDC(Deskhdc); // create a device context to use yourself

	plogger->writeDebug("Succesfully got the Device Context for the Window/Screen", this->getTime());

	int width;
	int height;

	if (window == NULL) {
		// get the width and height of the screen
		width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		height = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	}
	else {
		RECT rect;
		GetWindowRect(window, &rect);

		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	plogger->writeDebug("Successfully got the Size of the Window/Screen", this->getTime());

	// create a bitmap
	HBITMAP bitmap = CreateCompatibleBitmap(Deskhdc, width, height);

	// use the previously created device context with the bitmap
	SelectObject(hDesk, bitmap);

	plogger->writeDebug("Successfully linked the HBitmap to the Device Context", this->getTime());

	// copy from the desktop device context to the bitmap device context
	// call this once per 'frame'
	int x = 0;
	if (monitorCount > 1) {
		if (monitorCount % 2 != 0) {
			x = ((width / monitorCount) * (int)((monitorCount - 1) / 2)) * -1;
		}
	}
	BitBlt(hDesk, 0, 0, width, height, Deskhdc, x, 0, SRCCOPY);

	plogger->writeDebug("Successfully copied the Image to the HBitmap", this->getTime());

	// after the recording is done, release the desktop context you got..
	ReleaseDC(NULL, Deskhdc);

	// ..and delete the context you created
	DeleteDC(hDesk);

	plogger->writeDebug("Successfully released or deleted the Device contexts", this->getTime());

	return bitmap;
}