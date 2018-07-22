#include "ScreenShots.h"

ScreenShots::ScreenShots(string savePath, int monitorAmount, Logger* plogger) {

	saveDir = savePath;
	monitorCount = monitorAmount;
	logger = plogger;

}