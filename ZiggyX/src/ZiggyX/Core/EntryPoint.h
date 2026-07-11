#pragma once

#ifdef ZX_PLATFORM_WINDOWS

extern ZiggyX::Application* ZiggyX::CreateApplication();

int main(int argc, char** argv)
{
	// Initialize all subsystems here

	auto app = ZiggyX::CreateApplication();
	app->Run();
	app->Stop();
}

#endif