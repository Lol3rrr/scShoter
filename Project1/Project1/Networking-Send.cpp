#define WIN32_LEAN_AND_MEAN

#include "Networking.h"

#include <shellapi.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

SOCKET createSocket(string ip, string port, WSADATA* wsaData) {
	int iResult;
	SOCKET sock;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (sock == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
		}

		// Connect to server.
		iResult = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(sock);
			sock = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	return sock;
}

void Networking::sendFile(string filePath, string fileName) {

	WSADATA wsaData;
	SOCKET ConnectSocket = createSocket("128.0.120.48", "23510", &wsaData);
	int iResult;

	std::cout << "Connection has been made\n";

	int bufferSize = 2;

	// Sending data about file
	long size = utils.getFileSize(filePath.c_str());

	string informationStr = "size:" + to_string(size) + "filename:" + fileName + "bufferSize:" + to_string(bufferSize);
	send(ConnectSocket, informationStr.c_str(), 1024, 0);

	cout << "Send Information: " << informationStr << endl;



	// Sending File
	ifstream in(filePath, ios::binary);

	int toRead = bufferSize;
	char* sendbuffer = new char[bufferSize];

	while (size > 0) {
		if (size < bufferSize)
			toRead = size;

		in.read(sendbuffer, toRead);
		send(ConnectSocket, sendbuffer, toRead, 0);

		size = size - toRead;
	}
	delete sendbuffer;

	string website = "";
	char* receiveBuffer = new char[1024];

	recv(ConnectSocket, receiveBuffer, 1024, 0);

	string linkMessage(receiveBuffer);

	if (linkMessage.find("link:") != string::npos) {
		website = linkMessage.substr(linkMessage.find("link:") + 5);
		cout << "Website: " << website.c_str() << endl;

		ShellExecute(0, 0, website.c_str(), 0, 0, SW_SHOW);
	}

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

}