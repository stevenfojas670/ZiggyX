#include "Game.h"

namespace ZiggyX
{
	Game* Game::s_Instance = nullptr;

	Game::Game()
	{
		// Initialize the window
		// Make this customizable later
		m_Window = std::make_unique<Window>();
	}

	Game::~Game()
	{

	}

	void Game::Start()
	{
		m_Running = true;
		while (m_Running && !m_Window->ShouldClose())
		{
			m_Window->OnUpdate();
		}
	}

	void Game::Shutdown()
	{
		// Trigger all system shutdowns
	}
}