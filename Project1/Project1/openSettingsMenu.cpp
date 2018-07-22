#include "Settings.h"

void clearConsole() {
	cout << string(100, '\n');
}

bool Settings::openSettingsMenu() {

	while (true) {

		// print out the standard message at the start of the 
		cout << "Settings: " << endl;
		cout << " -saveDir=" << JsonSettings["saveDir"] << endl;
		cout << " -monitorCount=" << JsonSettings["monitorCount"] << endl;
		cout << " -videocapture=" << JsonSettings["screencapture"] << endl;
		cout << " -debug=" << JsonSettings["debug"] << endl;

		// get the input from the user
		string settingStr;
		getline(cin, settingStr);

		// clear out the console so it doesnt get messy(er)
		clearConsole();

		// check if the user wants to exit the settings mode
		if (settingStr.find("exit") != string::npos) {
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

		if (strcmp(args.c_str(), "videocapture") == 0) {
			// check if new value is provided
			if (valueStart < settingStr.length()) {
				// get new value
				string value = settingStr.substr(valueStart, settingStr.length() - valueStart);

				bool boolValue;

				if (strcmp(value.c_str(), "true") == 0) {
					boolValue = true;

					JsonSettings["screencapture"] = boolValue;
					cout << "Videocapturing has been turned on" << endl;
				}
				else if (strcmp(value.c_str(), "false") == 0) {
					boolValue = false;

					JsonSettings["screencapture"] = boolValue;
					cout << "Videocapturing has been turned off" << endl;
				}
				else {
					cout << "An error occurred while getting the new Value" << endl;
					cout << "Please enter a value between 'true' or 'false'" << endl;
				}
			}
		}

		if (strcmp(args.c_str(), "debug") == 0) {
			// check if new value is provided
			if (valueStart < settingStr.length()) {
				// get new value
				string value = settingStr.substr(valueStart, settingStr.length() - valueStart);

				bool boolValue;

				if (strcmp(value.c_str(), "true") == 0) {
					boolValue = true;

					JsonSettings["debug"] = boolValue;
					cout << "Debuging Mode has been turned on" << endl;
				}
				else if (strcmp(value.c_str(), "false") == 0) {
					boolValue = false;

					JsonSettings["debug"] = boolValue;
					cout << "Debuging Mode has been turned off" << endl;
				}
				else {
					cout << "An error occurred while getting the new Value" << endl;
					cout << "Please enter a value between 'true' or 'false'" << endl;
				}
			}
		}
	}

	return false;
}