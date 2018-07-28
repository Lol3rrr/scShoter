#include "Settings.h"

Settings::Settings(string dataFolder, Utils* util) {
	utils = util;

	char* appdata = nullptr;
	size_t sz = 0;
	_dupenv_s(&appdata, &sz, "APPDATA");
	
	// declare two strings with the save paths
	appdataFolder = string(appdata) + "\\" + dataFolder + "\\";
	settingsFile = appdataFolder + "settings.json";

	

	// get the size of the settingsfile
	struct stat st;
	stat(settingsFile.c_str(), &st);
	int size = st.st_size;

	// read a JSON file
	if (size > 0) {
		// create input stream to settingsfile
		ifstream in(settingsFile);

		// parse the content of settingsfile to the settings json objekt
		JsonSettings = json::parse(in);

		// clear and close the input stream when its done
		in.clear();
		in.close();
	}

	// create a buffer for the desktop path
	char desktopPath[1024];
	util->getDesktopPath(desktopPath); // set the buffer to the desktop path

									   // get the default save path directory
	string defaultSavePath(desktopPath);

	// sets the default monitor count
	default_saveDir = defaultSavePath + "\\";
	default_monitorCount = 1;
	default_bufferSize = 256;
	default_debug = false;
	default_screencapture = false;
	default_upload = false;
	default_saveImage = true;
	default_minimize = false;

	// check if the imagedir was loaded
	if (JsonSettings["saveDir"].is_null()) {
		// set the imagedir to the default value
		JsonSettings["saveDir"] = default_saveDir;
	}
	if (JsonSettings["monitorCount"].is_null()) {
		// set the monitor Count to the default value
		JsonSettings["monitorCount"] = default_monitorCount;
	}
	if (JsonSettings["debug"].is_null()) {
		// set the debug mode to the default value
		JsonSettings["debug"] = default_debug;
	}
	if (JsonSettings["screencapture"].is_null()) {
		// set the debug mode to the default value
		JsonSettings["screencapture"] = default_screencapture;
	}
	if (JsonSettings["upload"].is_null()) {
		// set the debug mode to the default value
		JsonSettings["upload"] = default_upload;
	}
	if (JsonSettings["saveImage"].is_null()) {
		// set the debug mode to the default value
		JsonSettings["saveImage"] = default_saveImage;
	}
	if (JsonSettings["minimize"].is_null()) {
		// set the debug mode to the default value
		JsonSettings["minimize"] = default_minimize;
	}
	if (JsonSettings["bufferSize"].is_null()) {
		// set the debug mode to the default value
		JsonSettings["bufferSize"] = default_bufferSize;
	}
}