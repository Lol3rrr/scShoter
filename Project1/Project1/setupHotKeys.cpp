#include "Main.h"

void Main::setupHotKeys() {
	// Desktop screenshot 
	bool success = RegisterHotKey(
		NULL,
		1,
		MOD_CONTROL,
		0x7A);
	success = RegisterHotKey(
		NULL,
		2,
		MOD_SHIFT,
		0x7A);

	success = RegisterHotKey(
		NULL,
		3,
		MOD_CONTROL,
		0x7B);

	success = RegisterHotKey(
		NULL,
		4,
		MOD_CONTROL | MOD_SHIFT,
		0x54);

	if (success) {
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0) != 0) {
			if (msg.message == WM_HOTKEY)
			{
				switch (msg.wParam)
				{
				case 1:
					screenshots->takeDesktopScreenshot(settings->JsonSettings["debug"]);
					break;
				case 2:
					screenshots->takeFocusedScreenshot(settings->JsonSettings["debug"]);
					break;
				case 3:
					capturer->save(settings->JsonSettings["saveDir"], utils->getTime());
					break;
				case 4:
					console = true;
					break;
				}
			}
		}
	}
}