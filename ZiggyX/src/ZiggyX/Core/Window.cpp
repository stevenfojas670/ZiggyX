#include "ZiggyX/Core/Window.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_log.h>


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
		// Implement event handling here
		SDL_Event event;
		while(SDL_POLLEVENT(&event))
		{
			switch(event)
			{
				case SDL_KeyboardEvent:
					// Push an event category with a specific callback to the event system
					// The dispatcher will dispatch the event and a subscriber will
					// handle the category with the specific event and do something
				break;
				case SDL_WindowEvent:
				break;
				case SDL_MouseButtonEvent:
				break;
				case SDL_MouseMotionEvent:
				break;
			}
		}
	}
}