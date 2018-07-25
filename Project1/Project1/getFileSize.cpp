#include "Utils.h"

long Utils::getFileSize(const char* path) {

	FILE* ftemp = fopen(path, "r");
	fseek(ftemp, 0, SEEK_END);
	long size = ftell(ftemp);
	fseek(ftemp, SEEK_END, 0);
	fclose(ftemp);

	return size;
}