#include "Utils.h"

void Utils::getDesktopPath(char* array) {
	// Allocate a pointer to an Item ID list
	LPITEMIDLIST pidl;

	// Get a pointer to an item ID list that represents the path of a special folder
	HRESULT hr = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOPDIRECTORY, &pidl);

	// Convert the item ID list's binary representation into a file system path
	BOOL f = SHGetPathFromIDList(pidl, array);

	// Allocate a pointer to an IMalloc interface
	LPMALLOC pMalloc;

	// Get the address of our task allocator’s IMalloc interface
	hr = SHGetMalloc(&pMalloc);

	// Free the item ID list allocated by SHGetSpecialFolderLocation
	pMalloc->Free(pidl);

	// Free our task allocator
	pMalloc->Release();
}