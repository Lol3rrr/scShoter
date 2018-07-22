#pragma once
#include "json.hpp"
#include <fstream>
#include <sys/stat.h>
#include <iostream>

#include "Utils.h"
#include "Logger.h"

using namespace std;

using json = nlohmann::json;

class Settings
{
public:
	
	json JsonSettings;

	Settings(string dataFolder, Utils* utils);

	void safeSettings();
	bool openSettingsMenu(Utils* util);

private:

	int default_monitorCount;
	bool default_debug;
	bool default_screencapture;
	string default_saveDir;
	string settingsFile;
	string appdataFolder;

	Utils* utils;
};