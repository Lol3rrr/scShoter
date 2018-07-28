#include "Networking.h"

Networking::Networking(Logger* plogger, int buffersize)
{
	logger = plogger;
	bufferSize = buffersize;
}

Networking::~Networking()
{
}