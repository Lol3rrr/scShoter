#include "FileUploadInterface.h"

void FileUploadInterface::listening() {

	int clientSocket;
	char buffer[1024];
	int lstn;
	struct sockaddr_in client;

	lstn = listen(serverSocket, 5);
	if (lstn<0) {
		cout << "Error listening\n";
	}

	cout << "Server is listening\n";

	socklen_t len = sizeof(client);

	while (true) {
		clientSocket = accept(serverSocket, (struct sockaddr*)&client, &len);
		if (clientSocket<0) {
			cout << "Error accepting\n";
		}

		cout << "New Connection" << endl;

		// Receive Data about file
		recv(clientSocket, buffer, 1024, 0);
		string message(buffer);
		int sizeIndex = message.find("size:");
		int fileNameIndex = message.find("filename:");
		int bufferIndex = message.find("bufferSize:");

		int sizeLength = message.length() - fileNameIndex - 5;

		long long size = stoi(message.substr(sizeIndex + 5, sizeLength));
		int bufferSize = stoi(message.substr(bufferIndex + 11));

		int fileNameLength = message.length() - to_string(bufferSize).length() - 9 - to_string(size).length() - 5 - 11;

		string fileName = message.substr(fileNameIndex + 9, fileNameLength);

		cout << "Size: " << size << endl;
		cout << "File Name: " << fileName << endl;
		cout << "Buffer: " << bufferSize << endl;

		// Receive File
		cout << "Starting to receive data..." << endl;

		string destination = "/var/www/html/uploads/" + fileName;

		ofstream out(destination, ios::trunc | ios::binary);

		int toRead = bufferSize;
		char recvBuffer[bufferSize];

		while (size > 0) {
			if (size < bufferSize)
				toRead = size;

			size = size - recv(clientSocket, recvBuffer, toRead, 0);
			out.write(recvBuffer, toRead);
		}

		out.close();

		cout << "Received all Data" << endl;

		cout << "Sending link..." << endl;

		string linkBuffer = "link:http://lol3r.net/uploads/" + fileName;
		cout << "Link: " << linkBuffer << endl;
		send(clientSocket, linkBuffer.c_str(), 1024, 0);

		cout << "Link has been sent" << endl;

		close(clientSocket);
		shutdown(clientSocket, 0);

		cout << "Closed Connection" << endl;
	}

}