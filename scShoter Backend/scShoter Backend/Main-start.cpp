#include "Main.h"

void Main::start() {

	socketThread = new thread(&FileUploadInterface::start , fileUploadInterface);

	while (true) {
		string command;
		getline(cin, command);

		if (command.find("stop") != string::npos) {
			break;
		}
	}

}