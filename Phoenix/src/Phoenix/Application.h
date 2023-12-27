#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Phoenix 
{
	class PHOENIX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
	};

	Application* CreateApplication();
}
