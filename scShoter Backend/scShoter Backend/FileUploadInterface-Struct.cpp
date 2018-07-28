#include "FileUploadInterface.h"

FileUploadInterface::FileUploadInterface(uint Serverport, int maxAmountConnections) {

	port = Serverport;
	maxConnections = maxAmountConnections;

	threads = vector<thread>(maxAmountConnections);

}

FileUploadInterface::~FileUploadInterface() {

}