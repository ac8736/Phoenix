#pragma once

#include "Event.h"

namespace Phoenix {
	class PHOENIX_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		static EventType GetStaticType() { return EventType::AppTick; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "AppTick";
		}
	};

	class PHOENIX_API AppUpdateEvent : public Event {
		AppUpdateEvent() {}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		static EventType GetStaticType() { return EventType::AppUpdate; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "AppUpdate";
		}
	};

	class PHOENIX_API AppRenderEvent : public Event {
		AppRenderEvent() {}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		static EventType GetStaticType() { return EventType::AppRender; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "AppRender";
		}
	};

	class PHOENIX_API WindowCloseEvent : public Event {
		WindowCloseEvent() {}

		static EventType GetStaticType() { return EventType::WindowClose; }

		EventType GetEventType() const {
			return GetStaticType();
		}

		const char* GetName() const {
			return "WindowClose";
		}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}
	};

	class PHOENIX_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_WindowWidth(width), m_WindowHeight(height) {}

		unsigned int GetWidth() const { return m_WindowWidth; }

		unsigned int GetHeight() const { return m_WindowHeight; }

		static EventType GetStaticType() { return EventType::WindowResize; }

		EventType GetEventType() const { 
			return GetStaticType();
		}

		const char* GetName() const {
			return "WindowResize";
		}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		std::string ToString() const { 
			std::stringstream ss;
			ss << "Window Resize: (width: " << m_WindowWidth << ", height: " << m_WindowHeight << ")";
			return ss.str();
		}
	private:
		unsigned int m_WindowWidth, m_WindowHeight;
	};


	class PHOENIX_API WindowFocusEvent : public Event {

	};

	class PHOENIX_API WindowLostFocusEvent : public Event {

	};

	class PHOENIX_API WindowMovedEvent : public Event {

	};
}