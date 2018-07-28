#include "ScreenShots.h"

ScreenShots::ScreenShots(string savePath, int monitorAmount, bool saveImage, bool uploadImage, Networking* pnetworking, Logger* plogger) {

	networking = pnetworking;
	logger = plogger;

	logger->writeDebug("Initializing Screenshoter", utils.getTime());

	monitorCount = monitorAmount;

	saveDir = savePath;
	save = saveImage;
	upload = uploadImage;

	logger->writeDebug("Initialized Screenshoter", utils.getTime());

}