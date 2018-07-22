#include "Utils.h"

string Utils::getTime() {
	time_t rawtime;
	struct tm timeinfo;
	char buffer[1024];

	std::time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y--%H-%M-%S", &timeinfo);
	string time(buffer);
	return time;
}