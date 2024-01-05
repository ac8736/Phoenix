#pragma once

#include "Phoenix/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Phoenix {
	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowhandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}