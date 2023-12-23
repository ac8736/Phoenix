#pragma once

#include "Event.h"

namespace Phoenix {

	// mouse move event, carries the mouse's x, y position after it moves
	class PHOENIX_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float mouseX, float mouseY) : m_MouseX(mouseX), m_MouseY(mouseY) {}
		
		int GetCategoryFlags() const override {
			return EventCategoryInput | EventCategoryMouse;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: (x: " << m_MouseX << " , y: " << m_MouseY << ")";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "MouseMoved";
		}

		float GetX() const { return m_MouseX; }
		
		float GetY() const { return m_MouseY; }

	private:
		float m_MouseX, m_MouseY;
	};

	// mouse scroll event, records the scroll x, y offsets after a scroll
	class PHOENIX_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xoffset, float yoffset) : m_XOffset(xoffset), m_YOffset(yoffset) {}

		int GetCategoryFlags() const override {
			return EventCategoryInput | EventCategoryMouse;
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Scrolled Event: (x: " << m_XOffset << " , y: " << m_YOffset << ")";
			return ss.str();
		} 

		static EventType GetStaticType() { return EventType::MouseScrolled; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "MouseScrolled";
		}

		float GetX() const { return m_XOffset; }

		float GetY() const { return m_YOffset; }
	private:
		float m_XOffset, m_YOffset;
	};

	// parent mouse button class, stores the mouse button that was pressed
	class PHOENIX_API MouseButton : public Event {
	public:
		int GetKeyCode() const { return m_MouseButton; }

		int GetCategoryFlags() const override {
			return EventCategoryInput | EventCategoryMouse;
		}
	protected:
		MouseButton(int button) : m_MouseButton(button) {}

		int m_MouseButton;
	};

	// event for mouse button presses
	class PHOENIX_API MouseButtonPressedEvent : public MouseButton {
	public:
		MouseButtonPressedEvent(int button) : MouseButton(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Button Pressed: " << m_MouseButton;
			return ss.str();
		}

		const char* GetName() const override {
			return "MouseButtonPressed";
		}
	};

	// event for mouse button releases
	class PHOENIX_API MouseButtonReleasedEvent : public MouseButton {
	public:
		MouseButtonReleasedEvent(int button) : MouseButton(button) {}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Button Released: " << m_MouseButton;
			return ss.str();
		}

		const char* GetName() const override {
			return "MouseButtonReleased";
		}
	};
}