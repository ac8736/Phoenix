#pragma once
#include <string>

#include <glm/glm.hpp>

namespace Phoenix {
	class Shader {
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const uint32_t GetShaderID() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}