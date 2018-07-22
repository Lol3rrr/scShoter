#include "ScreenShots.h"

void ScreenShots::takeFocusedScreenshot(bool debug) {
	logger->writeDebug("Starting Process to take a Screenshot of the focused Window", utils.getTime());

	HWND windowHWnd = GetForegroundWindow(); // get the Handle for 

	logger->writeDebug("Successfully got the Handler for the Window", utils.getTime());

	HBITMAP hbWindow = utils.getBitmap(windowHWnd, 0, logger);

	logger->writeDebug("Successfully got the HBitmap for the Window", utils.getTime());

	// attach the bitmap to the an image object
	CImage Focusedimage;
	Focusedimage.Attach(hbWindow);

	logger->writeDebug("Successfully attached the HBitmap to the Image Objekt", utils.getTime());

	// create string for File
	string save = saveDir + "Window-" + utils.getTime() + ".png";

	logger->writeDebug("Set the save Path for the Image to: " + save, utils.getTime());

	// Save the Image
	Focusedimage.Save(save.c_str());

	logger->writeDebug("Successfully saved the Image to the File", utils.getTime());

	// delete the bitmap object
	DeleteObject(hbWindow);

	logger->writeDebug("Successfully deleted the HBitmap Object", utils.getTime());
}