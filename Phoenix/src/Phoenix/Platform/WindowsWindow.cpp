#include "pnpch.h"

#include "WindowsWindow.h"
#include "Phoenix/Log/Log.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/KeyEvent.h"
#include "Phoenix/Events/MouseEvent.h"
#include "glad/glad.h"

namespace Phoenix {
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int error_code, const char* description) {
		PN_CORE_ERROR("GLFW Error {0}: {1}", error_code, description);
	}

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
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// using glfw to create the window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PN_CORE_ASSERT(status, "Failed to initialize Glad.");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// setting up glfw callbacks; which calls the EventCallback function inside the WindowData struct with the event triggered
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;

			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent mousePressed(button);
					data.EventCallback(mousePressed);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent mouseReleased(button);
					data.EventCallback(mouseReleased);
					break;
				}
			}
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent keyPressed(key, 0);
					data.EventCallback(keyPressed);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent keyReleased(key);
					data.EventCallback(keyReleased);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent keyRepeat(key, 1);
					data.EventCallback(keyRepeat);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(character);
			data.EventCallback(event);
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(xoffset, yoffset);
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
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
