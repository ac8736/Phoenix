#include "pnpch.h"
#include "OpenGLContext.h"
#include "Phoenix/Log/Log.h"

#include "glad/glad.h"

namespace Phoenix {
	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle) : m_WindowHandle(windowhandle) {
		PN_CORE_ASSERT(m_WindowHandle, "Window Handle is null.");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PN_CORE_ASSERT(status, "Failed to initialize Glad.");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}