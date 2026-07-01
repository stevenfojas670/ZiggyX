#include "WindowsWindow.h"

namespace ZiggyX
{
	WindowsWindow::WindowsWindow(const WindowSpecification& specs)
	{
		Init(specs);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{

	}
	
	void WindowsWindow::Init(const WindowSpecification& specs)
	{
		// Init with SDL
	}

	void WindowsWindow::Shutdown()
	{
		// Call SDL window life cycle close
	}
}