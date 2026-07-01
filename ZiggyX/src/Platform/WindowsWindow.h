#pragma once

#include "ZiggyX/Core/Window.h"
#include <SDL3/SDL_video.h>

namespace ZiggyX
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecification& specs = WindowSpecification());

		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }
	private:
		virtual void Init(const WindowSpecification& specs = WindowSpecification());
		virtual void Shutdown();

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}