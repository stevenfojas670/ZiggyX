#pragma once

#include "ZiggyX/Events/Event.h"
#include <string>
#include <functional>
#include <Windows.h>

namespace ZiggyX
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1600;
		uint32_t Height = 900;
		bool IsResizeable = true;

		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn EventCallback;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowSpecification& specs = WindowSpecification());
		virtual ~Window();

		virtual	void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

	private:
		WindowSpecification m_Specification;
	};
}