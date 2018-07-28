#include "ScreenShots.h"

void ScreenShots::saveImage(string saveName, CImage* image) {

	string savePath = "";

	if (save) {
		savePath = saveDir + saveName;
	}
	else {
		savePath = tmpnam(nullptr);
		savePath += ".png";
	}

	logger->writeDebug("Set the save Path for the Image to: " + savePath, utils.getTime());

	// save image
	image->Save(savePath.c_str());

	logger->writeDebug("Successfully saved the Image Object", utils.getTime());

	Sleep(50);

	if (upload) {
		networking->sendFile(savePath, saveName);
	}

}