#include "pnpch.h"

#include "WindowsWindow.h"
#include "Phoenix/Log.h"

namespace Phoenix {
	static bool s_GLFWInitialized = false;

	// will create a new Windows window instance
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	// initializes glfw
	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	// shutdown the app
	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	// initialize glfw and window properties
	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		PN_CORE_INFO("Window {0} of width {1} and height {2} is being created.", props.Title, props.Width, props.Height);

		// check if glfw is initialized, if not then initialize
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			// assertion macro to stop program if glfw could not initialize
			PN_CORE_ASSERT(success, "GLFW could not initialize.");
			s_GLFWInitialized = true;
		}

		// using glfw to create the window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	// destroy glfw window on shutdown
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	// on update function that updates the screen on every loop
	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	// enables vsync
	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}