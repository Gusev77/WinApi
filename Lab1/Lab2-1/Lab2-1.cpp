﻿#include <Windows.h>
#include <tchar.h>
#include <time.h>

int winWidth = 480;
int winHeight = 360;
int x = 30;
int y = 100;
unsigned int step = 100;

WNDCLASS wc;
int r = 255, g = 0, b = 255;

HBRUSH color_of_window = CreateSolidBrush(RGB(r, g, b));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
TCHAR WinTitle[] = _T("Окно 1");
TCHAR WinName2[] = _T("MainFrame2");
TCHAR WinTitle2[] = _T("Окно 2");

int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode) {
	HWND hWnd;
	MSG msg;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = color_of_window;

	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		WinTitle,
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		winWidth,
		winHeight,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HWND h = FindWindow(WinName2, WinTitle2);
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
	break; case WM_LBUTTONUP:
	{
		if (h) {
			int success = MessageBox(hWnd, _T("Окно 2 открыто!"), _T("Очень важное сообщение"), MB_OK);
			if (success) {
				SendMessage(h, WM_USER + 1, WPARAM(hWnd), 0);
			}
		}
		else
			MessageBox(hWnd,
				_T("Окно 2 закрыто!"),
				_T("НЕ Очень важное сообщение"), MB_OK);
		break;
	case WM_RBUTTONUP:
		if (h) {
			SendMessage(h, WM_USER + 2, WPARAM(hWnd), 0);
			ExitWindows(EWX_REBOOT, 0);  // функция выхода из системы

		}
		else
			MessageBox(hWnd,
				_T("Окно 2 закрыто!"),
				_T("Сообщение"), MB_OK);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
