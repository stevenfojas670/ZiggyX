#pragma once

namespace ZiggyX
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = 0;

		void Run();
		void Stop();
	};
}