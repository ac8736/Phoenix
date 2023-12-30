#pragma once

#include "Event.h"

namespace Phoenix {

	// parent KeyEvent class, stores the keycode of a key event
	class PHOENIX_API KeyEvent : public Event {
	public:
		int GetKeyCode() const { return m_KeyCode; }

		int GetCategoryFlags() const override {
			return EventCategoryInput | EventCategoryKeyboard;
		}

	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	// event for key presses
	class PHOENIX_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int keyPressAmount) : KeyEvent(keycode), m_RepeatAmount(keyPressAmount) {}

		int GetRepeatAmount() const { return m_RepeatAmount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Pressed Event: " << m_KeyCode << " (" << m_RepeatAmount << " repeats)";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "KeyPressed";
		}
	
	private:
		int m_RepeatAmount;
	};

	// event for key is released
	class PHOENIX_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Released Event: " << m_KeyCode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }

		virtual EventType GetEventType() const override {
			return GetStaticType();
		}

		virtual const char* GetName() const override {
			return "KeyReleased";
		}
	};

	// event for key presses
	class PHOENIX_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key Typed Event: " << m_KeyCode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyTyped; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "KeyTyped";
		}
	};
}