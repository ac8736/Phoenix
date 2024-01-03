#pragma once

#include "pnpch.h"
#include "Phoenix/Core.h"

namespace Phoenix {
	// Events in Phoenix are blocking, meaning when an event occurs, we stop and dispatch. we can defer it into a queue in the future and execute on a update or tick

	// all the different events that can occur in the window
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// categorize the events to grab groups of events, rather than having individual checks for each item in the category
	// ie. keyPressed & keyReleased both are in the category of EventCategoryKeyboard
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMousePressed = BIT(4)
	};

	// base Event class that all other events will inherit from
	class PHOENIX_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		// checks the event category with EventCategory enum
		bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & category; }
		inline bool IsHandled() const { return handled; }
	
	protected:
		bool handled = false;
	};

	// Event dispatcher that will run callback functions when an event is triggered
	class EventDispatcher {
		template<typename T> using EventFn = std::function<bool(T&)>;
	public:
		// constructor initializer list
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;	
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
