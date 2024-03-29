#pragma once

#include "pnpch.h"

#include "Events/Event.h"
#include "Core.h"

namespace Phoenix {
	// will contain the basic window information
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title="Phoenix Engine", 
					unsigned int width=1440, 
					unsigned int height=900) : Title(title), Width(width), Height(height) {}
	};

	// abstracting the Window class
	// platform independent, each platform must implement this interface
	class PHOENIX_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}