#include "Main.h"
#include "Networking.h"

Main::Main()
{
	console = false;

	string dataFolder = "scshoter";

	settings = new Settings(dataFolder, utils);
	logger = new Logger(dataFolder, settings->JsonSettings["debug"]);
	utils = new Utils();
	capturer = new VideoCapturer(logger);


	if (settings->JsonSettings["monitorCount"] == NULL) {
		int monitorCount = 1;

		cout << "Please Enter the Amount of Monitors you have: ";
		cin >> monitorCount;

		settings->JsonSettings["monitorCount"] = monitorCount;
	}

	screenshots = new ScreenShots(settings->JsonSettings["saveDir"], settings->JsonSettings["monitorCount"], logger);

	Networking network;

	cout << "Sending..." << endl;

	network.sendFile("D:/Tests/Screenshoter/Desk-21-07-2018--13-39-54.png", "Desk-21-07-2018--13-39-54.png");
	 
	cout << "Send" << endl;
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