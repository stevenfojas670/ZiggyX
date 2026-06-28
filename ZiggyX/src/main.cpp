#include <iostream>

/*
* Initialize systems via pointers
* Develop an event based architecture to read events and update state
*
* Systems:
* Event
* User Input
* Physics
* Rendering
*
* MVP:
* Event
* User Input
* Physics
*/

#include "ZiggyX/Core/Base.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	const wchar_t* pClassName = L"ZiggyX";
	const wchar_t* pWindowName = L"THE ZIGGY ENGINE";

	// Register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hInstance = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	// Create Window instance
	HWND hwnd = CreateWindowEx(
		0,
		pClassName,
		pWindowName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,
		200, 200, // PosX PosY
		1600, 900, // width, height
		nullptr, nullptr, hInstance, nullptr
	);

	if (hwnd == nullptr)
		return 0;

	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		// simple example of changing things on user input
		SetWindowText(hwnd, L"Keydown");
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}