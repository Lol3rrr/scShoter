#include "Main.h"

bool Main::filterCommand(string commandStr) {

	if (commandStr.find("exit") != std::string::npos) {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		console = false;
		return false;
	}
	else if (commandStr.find("stop") != std::string::npos) {
		settings->safeSettings();
		exit(0);
	}
	else if (commandStr.find("desk-screenshot") != std::string::npos) {
		screenshots->takeDesktopScreenshot(settings->JsonSettings["debug"]);
	}
	else if (commandStr.find("help") != std::string::npos) {
		writeHelp();
	}
	else if (commandStr.find("settings") != std::string::npos) {
		settingsMenu = true;
		return false;
	}

	return true;
}