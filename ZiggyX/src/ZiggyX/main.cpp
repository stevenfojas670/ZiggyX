#include <iostream>
#include "ZiggyX.h"

class Sandbox : public ZiggyX::Application
{
public:
	Sandbox();
	~Sandbox();
};


/*
* WindowProc will need a wrapper
* When detecting user input, the message should be sent to an event handler to process the category of
* input and the exact key. That data should then be sent to the proper event handlers.
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd); // Destroy window but also we need to shutdown the application
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // Destroy window but also we need to shutdown the application
		break;
	case WM_KEYDOWN:
	{
		wchar_t szFileName[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(nullptr);
		GetModuleFileName(hInstance, szFileName, MAX_PATH);
		MessageBox(hwnd, szFileName, L"This program is:", MB_OK | MB_ICONINFORMATION);
	}
	break; // Send data to event handlers
	case WM_LBUTTONDOWN:
		std::cout << "Left click" << std::endl;
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int main()
{
	HINSTANCE hInstance = GetModuleHandle(nullptr);
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

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Create Window instance
	HWND hwnd = CreateWindowEx(
		0,
		pClassName,
		pWindowName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,
		200, 200, // PosX PosY
		1280, 720, // width, height
		nullptr, nullptr, hInstance, nullptr
	);

	if (hwnd == nullptr)
	{
		MessageBox(
			NULL,
			L"Window creation failed!",
			L"Error!",
			MB_OK | MB_ICONERROR | MB_DEFBUTTON1
		);
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg = {};
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) // GetMessage() -> Looks into message queue
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		MessageBox(nullptr, L"Message Loop encountered an error!", L"Error!", MB_OK | MB_ICONERROR);
	}
	else
	{
		std::cout << static_cast<int>(msg.wParam) << std::endl;
	}

	return 0;
}
