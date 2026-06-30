#include "ZiggyX/Core/Window.h"

namespace ZiggyX
{
	Window::WindowClass::WindowClass() noexcept : hInst(GetModuleHandle(nullptr))
	{
		// Register window class
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hInstance = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
	}

	Window::WindowClass::~WindowClass()
	{
		UnregisterClass(this->wndClassName, GetInstance());
	}

	const wchar_t* Window::WindowClass::GetName() noexcept
	{
		return wndClassName;
	}

	HINSTANCE Window::WindowClass::GetInstance() noexcept
	{
		return wndClass.hInst;
	}

	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{

	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{

	}
}