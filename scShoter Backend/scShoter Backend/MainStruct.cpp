#include "Main.h"

Main::Main() {

	logger = new Logger("test.log", true);

}

Main::~Main() {

	delete(socketThread);
	delete(logger);

}