#pragma once

#ifdef ZX_PLATFORM_WINDOWS

extern ZiggyX::Application* ZiggyX::CreateApplication();

int main(int argc, char** argv)
{
	auto app = ZiggyX::CreateApplication();
	app->Start();
	app->Shutdown();
}

#endif