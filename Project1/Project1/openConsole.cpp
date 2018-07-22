#include "Main.h"

void Main::openConsole() {
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	while (true) {

		string commandStr;
		getline(cin, commandStr);

		if (!filterCommand(commandStr)) {
			break;
		}
	}
}