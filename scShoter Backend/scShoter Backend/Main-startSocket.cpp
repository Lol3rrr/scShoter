#include "Main.h"

#define PORT 23510
#define BACKLOG 5

void Main::startSocket() {

	int fd1, fd2;
	int bnd, lstn;
	char buffer[1024];
	struct sockaddr_in server, client;

	fd1 = socket(AF_INET, SOCK_STREAM, 0);
	if (fd1<0) {
		cout << "Error creating socket\n";
	}
	cout << "Socket created\n";

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;


	bnd = bind(fd1, (struct sockaddr *)&server, sizeof(server));
	if (bnd<0) {
		cout << "Error binding\n";
	}

	lstn = listen(fd1, BACKLOG);
	if (lstn<0) {
		cout << "Error listening\n";
	}

	cout << "Server is listening\n";

	socklen_t len = sizeof(client);

	while (true) {
		fd2 = accept(fd1, (struct sockaddr*)&client, &len);
		if (fd2<0) {
			cout << "Error accepting\n";
		}

		cout << "New Connection" << endl;

		// Receive Data about file
		recv(fd2, buffer, 1024, 0);
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

			size = size - recv(fd2, recvBuffer, toRead, 0);
			out.write(recvBuffer, toRead);
		}

		out.close();

		cout << "Received all Data" << endl;

		cout << "Sending link..." << endl;

		string linkBuffer = "link:http://lol3r.net/uploads/" + fileName;
		cout << "Link: " << linkBuffer << endl;
		send(fd2, linkBuffer.c_str(), 1024, 0);

		cout << "Link has been sent" << endl;

		close(fd2);
		shutdown(fd2, 0);

		cout << "Closed Connection" << endl;
	}

	close(fd1);
	shutdown(fd1, 0);

}