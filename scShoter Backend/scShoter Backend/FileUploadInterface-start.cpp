#include "FileUploadInterface.h"

void FileUploadInterface::start() {

	createSocket(port);

	listening();

}