// Injector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Injector.h"
#include "ProcessHelper.h"
#include <iostream>
#include "cstdio"
#include "TlHelp32.h"

const char* process = "fallout4.exe";


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DROPFILES: {
		HDROP hDrop = (HDROP)wParam;
		UINT fileCount = DragQueryFileW(hDrop, 0xFFFFFFFF, NULL, 0);
		if (fileCount > 0) {
			wchar_t filePath[MAX_PATH];
			DragQueryFileW(hDrop, 0, filePath, MAX_PATH);
			Injector injector;
			DWORD pId = 0;
			while (pId == 0) {
				pId = GetProcessIdFromName(process);
				Sleep(1);
			}
			Sleep(100);
		}
		DragFinish(hDrop);
		break;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "MyWindowClass";
	RegisterClass(&wc);

	// Create the window
	HWND hwnd = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		"MyWindowClass",
		"My Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance, NULL);

	if (hwnd == NULL) {
		return 1;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {

		if (GetAsyncKeyState(VK_F5) & 0x8000) {
			Injector injector;
			DWORD pId = 0;
			while (pId == 0) {
				pId = GetProcessIdFromName(process);
				Sleep(1);
			}
			Sleep(100);
			injector.inject(pId, L"C:\\Users\\xlear\\source\\repos\\Injector\\x64\\Debug\\Hack.dll");
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return (int)msg.wParam;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
