#include "FileUploadInterface.h"

void FileUploadInterface::createSocket(uint port) {

	int bnd;
	struct sockaddr_in server, client;

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket<0) {
		cout << "Error creating socket\n";
	}
	cout << "Socket created\n";

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;


	bnd = bind(serverSocket, (struct sockaddr *)&server, sizeof(server));
	if (bnd<0) {
		cout << "Error binding\n";
	}

}