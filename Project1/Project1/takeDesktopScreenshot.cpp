#include "ScreenShots.h"

void ScreenShots::takeDesktopScreenshot(bool debug) {
	HDC Deskhdc = GetDC(NULL); // get the desktop device context
	HDC hDesk = CreateCompatibleDC(Deskhdc); // create a device context to use yourself

	// get the width and height of the screen
	int width = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	// create a bitmap
	HBITMAP hbDesktop = CreateCompatibleBitmap(Deskhdc, width, height);

	// use the previously created device context with the bitmap
	SelectObject(hDesk, hbDesktop);

	// copy from the desktop device context to the bitmap device context
	// call this once per 'frame'
	int x = 0;
	if (monitorCount > 1) {
		if (monitorCount % 2 != 0) {
			x = ((width / monitorCount) * (int)((monitorCount - 1) / 2)) * -1;
		}
	}
	BitBlt(hDesk, 0, 0, width, height, Deskhdc, x, 0, SRCCOPY);

	if (debug) {
		cout << "[Debug] Screenshot offset X: " << x << " Screenshot width: " << width << " Screenshot height: " << height << endl;
	}

	// after the recording is done, release the desktop context you got..
	ReleaseDC(NULL, Deskhdc);

	// ..and delete the context you created
	DeleteDC(hDesk);

	// attach the bitmap to an image objekt
	CImage Deskimage;
	Deskimage.Attach(hbDesktop);

	// create the string for the savefile
	string save = saveDir + "Desk-" + utils.getTime() + ".png";
	
	if (debug) {
		cout << "[Debug] Image saving Path: " << save << endl;
	}

	// save image
	Deskimage.Save(save.c_str());

	// delete the bitmap object
	DeleteObject(hbDesktop);
}