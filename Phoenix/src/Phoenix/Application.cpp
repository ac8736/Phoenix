#include "pnpch.h"

#include "Application.h"
#include "Log.h"

#include "Events/ApplicationEvent.h"

namespace Phoenix
{
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		// --- testing event classes ---
		WindowResizeEvent e(1280, 720);
		PN_CLIENT_TRACE(e);
		// -----------------------------

		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}