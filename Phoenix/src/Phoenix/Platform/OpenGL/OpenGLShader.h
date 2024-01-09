#pragma once

#include "Phoenix/Renderer/Shader.h"

namespace Phoenix {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};
}