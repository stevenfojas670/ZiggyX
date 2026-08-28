#pragma once

#include "Core.h"
#include "Window.h"
#include <memory>

namespace ZiggyX
{
	/// <summary>
	/// This will be a singleton, requires a singleton check to ensure no other instances
	/// exist.
	/// Initializes Window, Renderer, and ImGUI.
	/// </summary>
	class ZX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Start();
		void Shutdown();

		// Getting the current singleton instance
		static Application& GetInstance() { return *s_Instance; }

	private:
		bool m_Running = false;
		std::unique_ptr<Window> m_Window;

	private:
		// Should be a singleton
		static Application* s_Instance;
	};

	Application* CreateApplication();
}