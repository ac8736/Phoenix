#include "pnpch.h"

#include "RenderCommand.h"
#include "Phoenix/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Phoenix {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}