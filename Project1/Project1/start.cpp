#include "Main.h"

void Main::startCapturer() {
	capturer->run(logger, utils);
}

void Main::start() {

	// starts a thread which listens for the hotkeys
	thread hotkeys(&Main::setupHotKeys, this);

	if (settings->JsonSettings["screencapture"]) {
		// start thread for the videocapturing
		thread captureing(&Main::startCapturer, this);
	}

	if (settings->JsonSettings["started"].is_null()) {
		settings->JsonSettings["started"] = true;
		writeHelp();
		console = true;
	}
	else if(settings->JsonSettings["minimize"]){
		// hides the console window
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	else {
		console = true;
	}

	while (true) {
		if (console) {
			if (settingsMenu) {
				settingsMenu = settings->openSettingsMenu();
			}
			openConsole();
		}
		Sleep(100);
	}

}