#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Log.h"

namespace Phoenix
{
	Application::Application() {
		
	}

	Application::~Application() {

	}

	void Application::Run() {
		// --- testing event classes ---
		WindowResizeEvent e(1280, 720);
		MouseButtonPressedEvent m(19);
		PN_TRACE(e);
		PN_INFO(m);
		// -----------------------------

		while (true);
	}
}