#include "Main.h"

Main::Main()
{
	console = false;

	string dataFolder = "scshoter";

	settings = new Settings(dataFolder, utils);
	logger = new Logger(dataFolder, settings->JsonSettings["debug"]);
	utils = new Utils();
	capturer = new VideoCapturer(logger);
	networking = new Networking(logger, settings->JsonSettings["bufferSize"]);

	if (settings->JsonSettings["monitorCount"] == NULL) {
		int monitorCount = 1;

		cout << "Please Enter the Amount of Monitors you have: ";
		cin >> monitorCount;

		settings->JsonSettings["monitorCount"] = monitorCount;
	}

	screenshots = new ScreenShots(settings->JsonSettings["saveDir"], settings->JsonSettings["monitorCount"], settings->JsonSettings["saveImage"], settings->JsonSettings["upload"], networking, logger);
}

Main::~Main()
{

	delete settings;
	delete screenshots;
	delete utils;
	delete capturer;
	delete logger;

	UnregisterHotKey(NULL, 1);
	UnregisterHotKey(NULL, 2);
	UnregisterHotKey(NULL, 3);
	UnregisterHotKey(NULL, 4);

}