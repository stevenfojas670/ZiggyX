#include "ZiggyX.h"

class Sandbox : public ZiggyX::Application
{
public:
	Sandbox() {}
	~Sandbox() {}
};

int main()
{
	Sandbox* sandbox = new Sandbox();

	sandbox->Run();

	return 0;
}