#include <ZiggyX/ZiggyX.h>

class Sandbox : public ZiggyX::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

ZiggyX::Application* ZiggyX::CreateApplication()
{
	return new Sandbox();
}