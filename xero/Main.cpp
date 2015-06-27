#include <Windows.h>
#include "resource.h"

const char g_szClassName[] = "Xero Frame";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = g_szClassName;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = 0;
	
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Error Registering class Ex", "Register Error", MB_OK);
		return -1;
	}

	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, hInstance, NULL);
	if (!hwnd)
	{
		MessageBox(NULL, "Error Creating Window Ex", "Create Error", MB_OK);
		return -1;
	}

	UpdateWindow(hwnd);
	ShowWindow(hwnd, nCmdShow);

	MSG msg;
	while (true)
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_QUIT) break;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (INT) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return true;
}