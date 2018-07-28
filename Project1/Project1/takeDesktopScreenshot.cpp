#include "ScreenShots.h"

void ScreenShots::takeDesktopScreenshot() {
	
	logger->writeDebug("Started Process to take a Screenshot of the Desktop", utils.getTime());

	HBITMAP hbDesktop = utils.getBitmap(NULL, monitorCount, logger);

	logger->writeDebug("Successfully got the HBitmap of the Desktop", utils.getTime());

	// attach the bitmap to an image objekt
	CImage Deskimage;
	Deskimage.Attach(hbDesktop);

	logger->writeDebug("Successfully attached the HBitmap to an Image Object", utils.getTime());

	// saving the Image
	string saveName = "Desk-" + utils.getTime() + ".png";

	saveImage(saveName, &Deskimage);

	// delete the bitmap object
	DeleteObject(hbDesktop);

	logger->writeDebug("Successfully deleted the HBitmap Object", utils.getTime());
}