#include "Settings.h"

void clearConsole() {
	cout << string(100, '\n');
}

void filterBoolean(string args, int valueStart, string overallStr, Settings* settings, string Keyword, string ModuleName, string settingsKey) {
	if (strcmp(args.c_str(), Keyword.c_str()) == 0) {
		// check if new value is provided
		if (valueStart < overallStr.length()) {
			// get new value
			string value = overallStr.substr(valueStart, overallStr.length() - valueStart);

			bool boolValue;

			if (strcmp(value.c_str(), "true") == 0) {
				boolValue = true;

				settings->JsonSettings[settingsKey] = boolValue;
				cout << ModuleName << " has been turned on" << endl;
			}
			else if (strcmp(value.c_str(), "false") == 0) {
				boolValue = false;

				settings->JsonSettings[settingsKey] = boolValue;
				cout << ModuleName << " has been turned off" << endl;
			}
			else {
				cout << "An error occurred while getting the new Value" << endl;
				cout << "Please enter a value between 'true' or 'false'" << endl;
			}
		}
	}
}

bool Settings::openSettingsMenu() {

	while (true) {

		// print out the standard message at the start of the 
		cout << "Commands: " << endl;
		cout << " - [Name of Setting]=[New Value] : to change a Setting" << endl;
		cout << " - exit : to get out of the Settings Menu and into the Normal console" << endl;
		cout << "Settings: " << endl;
		cout << " - saveDir=" << JsonSettings["saveDir"] << endl;
		cout << " - monitorCount=" << JsonSettings["monitorCount"] << endl;
		cout << " - videocapture=" << JsonSettings["screencapture"] << endl;
		cout << " - upload=" << JsonSettings["upload"] << endl;
		cout << " - saveimage=" << JsonSettings["saveImage"] << endl;
		cout << " - minimize=" << JsonSettings["minimize"] << endl;
		cout << " - buffersize=" << JsonSettings["bufferSize"] << endl;
		cout << " - debug=" << JsonSettings["debug"] << endl;

		// get the input from the user
		string settingStr;
		getline(cin, settingStr);

		// clear out the console so it doesnt get messy(er)
		clearConsole();

		// check if the user wants to exit the settings mode
		if (settingStr.find("exit") != string::npos) {
			this->safeSettings();
			break;
		}

		// get the setting argument
		string args = settingStr.substr(0, settingStr.find('='));
		int valueStart = settingStr.find("=") + 1;

		// check if the user wants to change the save dir
		if (strcmp(args.c_str(), "saveDir") == 0) {
			// check if new value is provided
			if (valueStart < settingStr.length()) {
				// get new value
				string value = settingStr.substr(valueStart, settingStr.length() - valueStart);

				//check if new savepath exists
				if (utils->DirExists(value)) {
					// get the ending of the new path
					char ending = value.back();
					// check if it ends on \ and add if not 
					if (ending != '\\') {
						value += "\\";
					}
					// changes the settings 
					JsonSettings["saveDir"] = value;
					// gives out that it was successful together with the new path
					cout << "New Save path is set to " << value << endl;
				}
				else {
					// give out that the given path is not a directory or doesnt exist
					cout << "This Path(" << value << ") does not exist or is not a Directory" << endl;
				}
			}
		}
		
		if (strcmp(args.c_str(), "monitorCount") == 0) {
			// check if new value is provided
			if (valueStart < settingStr.length()) {
				// get new value
				string value = settingStr.substr(valueStart, settingStr.length() - valueStart);

				int intValue = strtol(value.c_str(), nullptr, 10);

				JsonSettings["monitorCount"] = intValue;
				cout << "Monitor count has been set to " << intValue << endl;
			}
		}

		filterBoolean(args, valueStart, settingStr, this, "videocapture", "Videocapturing", "screencapture");
		filterBoolean(args, valueStart, settingStr, this, "debug", "Debuging Mode", "debug");
		filterBoolean(args, valueStart, settingStr, this, "upload", "Uploading", "upload");
		filterBoolean(args, valueStart, settingStr, this, "saveimage", "Image Saving", "saveImage");
		filterBoolean(args, valueStart, settingStr, this, "minimize", "Minimizing Console", "minimize");
		
	}

	return false;
}