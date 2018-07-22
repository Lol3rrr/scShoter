#include "Settings.h"

void Settings::safeSettings() {

	// checks if the directory of the settingsfile exitsts
	if (utils->DirExists(appdataFolder) == false) {
		// creates the directory of the settingsfile
		CreateDirectoryA(LPCTSTR(appdataFolder.c_str()), NULL);
	}

	// open an output stream to the settingsfile
	ofstream out(settingsFile);

	// write the settings json objekt in den settingsfile
	out << JsonSettings << endl;

	// closes the stream when its done writing
	out.close();
}