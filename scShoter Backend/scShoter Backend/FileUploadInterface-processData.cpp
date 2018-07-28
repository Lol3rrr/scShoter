#include "FileUploadInterface.h"

void FileUploadInterface::processData(int clientSocket) {

	char buffer[1024];

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
	int dotPos = fileName.find(".");
	string destinationFileName = fileName.substr(0, fileName.length() - 4) + "-" + to_string(rand()) + fileName.substr(dotPos);

	cout << "Size: " << size << endl;
	cout << "File Name: " << fileName << endl;
	cout << "Destination File Name: " << destinationFileName << endl;
	cout << "Buffer: " << bufferSize << endl;

	// Receive File
	cout << "Starting to receive data..." << endl;

	string destination = "/var/www/html/uploads/" + destinationFileName;

	ofstream out(destination, ios::binary);

	int toRead = bufferSize;
	char recvBuffer[bufferSize];

	while (size > 0) {
		if (size < bufferSize)
			toRead = size;

		recv(clientSocket, recvBuffer, toRead, 0);
		size -= toRead;
		out.write(recvBuffer, toRead);
	}

	out.close();

	cout << "Received all Data" << endl;

	cout << "Sending link..." << endl;

	string linkBuffer = "link:http://lol3r.net/uploads/" + destinationFileName;
	cout << "Link: " << linkBuffer << endl;
	send(clientSocket, linkBuffer.c_str(), 1024, 0);

	cout << "Link has been sent" << endl;

	close(clientSocket);
	shutdown(clientSocket, 0);

	cout << "Closed Connection" << endl;

	cout << "---------------------" << endl;

	connections -= 1;
}