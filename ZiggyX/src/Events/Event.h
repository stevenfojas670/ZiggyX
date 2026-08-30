#pragma once

// This is an individual event that a system can fire off
// What methods and properties are needed?

#include <string>
#include <functional>

namespace ZiggyX
{
	enum class EventCategory
	{
		KeyEvent,
		MouseEvent
	};

	enum class EventType
	{
		None = 0,
		KeyPressed,
		KeyReleased,
		MouseMove,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled
	};

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
	};

	class EventManager
	{
	public:
		EventManager(Event& event);
		void Subscribe();
		void Dispatch();
	private:
		Event& m_Event;
	};
}