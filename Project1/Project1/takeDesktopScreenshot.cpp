#include "ScreenShots.h"

void ScreenShots::takeDesktopScreenshot(bool debug) {
	
	logger->writeDebug("Started Process to take a Screenshot of the Desktop", utils.getTime());

	HBITMAP hbDesktop = utils.getBitmap(NULL, monitorCount, logger);

	logger->writeDebug("Successfully got the HBitmap of the Desktop", utils.getTime());

	// attach the bitmap to an image objekt
	CImage Deskimage;
	Deskimage.Attach(hbDesktop);

	logger->writeDebug("Successfully attached the HBitmap to an Image Object", utils.getTime());

	// create the string for the savefile
	string save = saveDir + "Desk-" + utils.getTime() + ".png";
	
	logger->writeDebug("Set the save Path for the Image to: " + save, utils.getTime());

	// save image
	Deskimage.Save(save.c_str());

	logger->writeDebug("Successfully saved the Image Object", utils.getTime());

	// delete the bitmap object
	DeleteObject(hbDesktop);

	logger->writeDebug("Successfully deleted the HBitmap Object", utils.getTime());
}