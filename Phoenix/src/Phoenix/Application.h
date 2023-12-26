#pragma once

#include "Core.h"
#include "Window.h"

namespace Phoenix 
{
	class PHOENIX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
	};

	Application* CreateApplication();
	bool m_Running = true;
}
