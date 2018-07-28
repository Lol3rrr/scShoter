#include "Main.h"

Main::Main() {

	logger = new Logger("test.log", true);
	fileUploadInterface = new FileUploadInterface(23510, 20);

}

Main::~Main() {

	delete(socketThread);
	delete(fileUploadInterface);
	delete(logger);

}