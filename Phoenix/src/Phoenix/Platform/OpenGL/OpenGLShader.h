#pragma once

#include "Phoenix/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Phoenix {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void SetUniformMat4(const glm::mat4& mat, const std::string& name);
		void SetUniformFloat4(const glm::vec4 vec, const std::string& name);

		const uint32_t GetShaderID() const override { return m_RendererID; }
	private:
		uint32_t m_RendererID;
	};
}