#pragma once

#include "Core.h"

namespace ZiggyX
{
	class ZX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Stop();
	};

	Application* CreateApplication();
}