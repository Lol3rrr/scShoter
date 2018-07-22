#include "ScreenShots.h"

void ScreenShots::takeFocusedScreenshot(bool debug) {
	HWND windowHWnd = GetForegroundWindow(); // get the Handle for 

	HDC Windhdc = GetWindowDC(windowHWnd); // get the device context of the Window
	HDC hWind = CreateCompatibleDC(Windhdc); // create a device context to use yourself

	// get the height and width of the screen
	RECT rect;
	GetWindowRect(windowHWnd, &rect);

	// get width and height of window
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// create a bitmap
	HBITMAP hbWindow = CreateCompatibleBitmap(Windhdc, width, height);

	// use the previously created device context with the bitmap
	SelectObject(hWind, hbWindow);

	// copy from the desktop device context to the bitmap device context
	BitBlt(hWind, 0, 0, width, height, Windhdc, 0, 0, SRCCOPY);

	// after the recording is done, release the desktop context you got..
	ReleaseDC(windowHWnd, Windhdc);

	// delete the context you created
	DeleteDC(hWind);

	// attach the bitmap to the an image object
	CImage Focusedimage;
	Focusedimage.Attach(hbWindow);

	// create string for File
	string save = saveDir + "Window-" + utils.getTime() + ".png";

	// Save the Image
	Focusedimage.Save(save.c_str());

	// delete the bitmap object
	DeleteObject(hbWindow);
}