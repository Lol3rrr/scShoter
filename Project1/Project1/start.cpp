#include "Main.h"

void Main::start() {

	// starts a thread which listens for the hotkeys
	thread hotkeys(&Main::setupHotKeys, this);

	if (settings->JsonSettings["screencapture"]) {
		// start thread for the videocapturing
		thread captureing(capturer->run);
	}

	if (settings->JsonSettings["started"].is_null()) {
		settings->JsonSettings["started"] = true;
		writeHelp();
		console = true;
	}
	else {
		// hides the console window
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}

	while (true) {
		if (console) {
			if (settingsMenu) {
				settingsMenu = settings->openSettingsMenu(utils);
			}
			openConsole();
		}
		Sleep(100);
	}

}