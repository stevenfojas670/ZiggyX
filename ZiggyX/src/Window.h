#pragma once

#include "Events/Event.h"
#include <string>
#include <memory>

namespace ZiggyX
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1600;
		uint32_t Height = 900;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& specs = WindowSpecification());
		virtual ~Window();

		void OnUpdate();
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		bool ShouldClose() const;

	private:
		void Startup(const WindowSpecification& specs);
		void Shutdown();
		struct WindowImpl;
		std::unique_ptr<WindowImpl> m_WindowImpl;
	};
}