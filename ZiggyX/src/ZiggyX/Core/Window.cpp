#include "ZiggyX/Core/Window.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_events.h>
#include <iostream>


namespace ZiggyX
{
	struct Window::WindowImpl
	{
		WindowSpecification m_Specification;
		SDL_Window* m_Window;
		bool done = false;
	};

	Window::Window(const WindowSpecification& specs)
		: m_WindowImpl(std::make_unique<WindowImpl>())
	{
		Startup(specs);
	}

	Window::~Window()
	{
		Shutdown();
	}

	uint32_t Window::GetWidth() const { return m_WindowImpl->m_Specification.Width; }

	uint32_t Window::GetHeight() const { return m_WindowImpl->m_Specification.Height; }

	void Window::Startup(const WindowSpecification& specs)
	{
		m_WindowImpl->m_Specification.Title = specs.Title;
		m_WindowImpl->m_Specification.Width = specs.Width;
		m_WindowImpl->m_Specification.Height = specs.Height;

		// Initialize SDL3 window
		if (!SDL_Init(SDL_INIT_VIDEO))
		{
			SDL_LogError(
				SDL_LOG_CATEGORY_APPLICATION,
				"Could not initialize SDL: %s\n",
				SDL_GetError()
			);

			Shutdown();
		}

		// Window creation
		m_WindowImpl->m_Window = SDL_CreateWindow(
			m_WindowImpl->m_Specification.Title.c_str(),
			m_WindowImpl->m_Specification.Width,
			m_WindowImpl->m_Specification.Height,
			SDL_WINDOW_RESIZABLE
		);

		if (m_WindowImpl->m_Window == nullptr)
		{
			SDL_LogError(
				SDL_LOG_CATEGORY_ERROR,
				"Could not create window: %s\n",
				SDL_GetError()
			);

			Shutdown();
		}
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_WindowImpl->m_Window);
		SDL_Quit();
	}

	void Window::OnUpdate()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_WINDOW_RESIZED:
				break;
			case SDL_EVENT_WINDOW_MOVED:
				break;
			case SDL_EVENT_WINDOW_MINIMIZED:
				break;
			case SDL_EVENT_WINDOW_MAXIMIZED:
				break;
			case SDL_EVENT_WINDOW_MOUSE_ENTER:
				break;
			case SDL_EVENT_WINDOW_MOUSE_LEAVE:
				break;
			case SDL_EVENT_KEY_DOWN:
				std::cout << event.key.key << std::endl;
				break;
			case SDL_EVENT_KEY_UP:
				std::cout << event.key.key << std::endl;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				break;
			}
		}
	}
}