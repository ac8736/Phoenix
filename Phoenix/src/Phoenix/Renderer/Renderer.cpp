#include "pnpch.h"
#include "Renderer.h"
#include "Phoenix/Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace Phoenix {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera) {
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform) {
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjectionMatrix");
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4(transform, "u_Transform");
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}