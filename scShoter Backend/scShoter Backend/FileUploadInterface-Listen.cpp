#include "FileUploadInterface.h"

void FileUploadInterface::listening() {

	int clientSocket;
	int lstn;
	struct sockaddr_in client;

	lstn = listen(serverSocket, 5);
	if (lstn<0) {
		cout << "Error listening" << endl;
	}
	else {
		cout << "Server is listening" << endl;
	}

	socklen_t len = sizeof(client);

	while (true) {
		clientSocket = accept(serverSocket, (struct sockaddr*)&client, &len);
		if (clientSocket<0) {
			cout << "Error accepting" << endl;
		}
		cout << "Accepted new Connection" << endl;

		while (connections >= maxConnections) {
		}
		
		connections += 1;

		new thread(&FileUploadInterface::processData, this, clientSocket);

	}

}