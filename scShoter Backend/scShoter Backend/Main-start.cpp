#include "Main.h"

void Main::start() {

	socketThread = new thread(&Main::startSocket, this);

}