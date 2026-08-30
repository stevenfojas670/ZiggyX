#pragma once

#include "Window.h"
#include <memory>

namespace ZiggyX
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

		void Start();
		void Shutdown();

		// Getting the current singleton instance
		static Game& GetInstance() { return *s_Instance; }

	private:
		bool m_Running = false;
		std::unique_ptr<Window> m_Window;

	private:
		// Should be a singleton
		static Game* s_Instance;
	};
}