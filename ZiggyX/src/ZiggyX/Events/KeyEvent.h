#include "ZiggyX/Events/Event.h"

// Handles keyboard input

namespace ZiggyX
{
	class KeyEvent : public Event
	{
	public:
		virtual bool VOnKeyDown(unsigned int const kcode) = 0;
		virtual bool VOnKeyUp(unsigned int const kcode) = 0;

	private:
	};
}