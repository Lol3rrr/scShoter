#include "Utils.h"

bool Utils::DirExists(string path) {
	DWORD dwAttrib = GetFileAttributes((LPCTSTR)path.c_str());

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}