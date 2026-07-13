#include "Application.h"

namespace ZiggyX
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		// Initialize the window
		// Make this customizable later
		m_Window = std::make_unique<Window>();
	}

	Application::~Application()
	{

	}

	void Application::Start()
	{
		m_Running = true;
		while (m_Running)
		{
		}
	}

	void Application::Shutdown()
	{
		// Trigger all system shutdowns
	}
}