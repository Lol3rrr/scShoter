#include "ScreenShots.h"

ScreenShots::ScreenShots(string savePath, int monitorAmount, Logger* plogger) {

	logger = plogger;

	logger->writeDebug("Initializing Screenshoter", utils.getTime());

	saveDir = savePath;
	monitorCount = monitorAmount;

	logger->writeDebug("Initialized Screenshoter", utils.getTime());

}