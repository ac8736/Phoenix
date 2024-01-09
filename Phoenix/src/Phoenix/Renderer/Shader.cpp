#include "pnpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Phoenix/Log/Log.h"
#include "Phoenix/Platform/OpenGL/OpenGLShader.h"

namespace Phoenix {
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: PN_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
		}

		PN_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}