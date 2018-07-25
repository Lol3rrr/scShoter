#include "Main.h"

void Main::start() {

	socketThread = new thread(&FileUploadInterface::start , fileUploadInterface);

	while (true) {

	}

}