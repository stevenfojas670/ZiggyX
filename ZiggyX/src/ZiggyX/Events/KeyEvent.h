// Handles keyboard input

namespace ZiggyX
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }
		virtual bool VOnKeyDown(unsigned int const kcode) = 0;
		virtual bool VOnKeyUp(unsigned int const kcode) = 0;
	};
}