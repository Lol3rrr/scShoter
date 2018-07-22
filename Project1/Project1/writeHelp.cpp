#include "Main.h"

void Main::writeHelp() {
	cout << "Button Combinations:" << endl;
	cout << " - Control + F11: Take a Screenshot of the entire Desktop" << endl;
	cout << " - Shift + F11: Take a Screenshot of the Window which is currently Focused" << endl;
	cout << " - Control + Shift + T: Open the Console window" << endl;
	cout << "Commands:" << endl;
	cout << " - exit : Closes the Console Window but the Program will still be running in the Background" << endl;
	cout << " - stop : Shuts the Programm down" << endl;
	cout << " - desk-screenshot : Take a screenshot of the current Desktop" << endl;
	cout << " - setting : Enter the Settings Menu" << endl;
}