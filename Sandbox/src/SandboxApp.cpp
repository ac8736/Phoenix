#include "Phoenix/Phoenix.h"
#include "imgui.h"
#include <imgui_internal.h>
#include <Phoenix/Platform/OpenGL/OpenGLShader.h>

class ExampleLayer : public Phoenix::Layer {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f) {
		m_VertexArray.reset(Phoenix::VertexArray::Create());
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		std::shared_ptr<Phoenix::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Phoenix::VertexBuffer::Create(vertices, sizeof(vertices)));

		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "a_Position" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		m_VertexArraySquares.reset(Phoenix::VertexArray::Create());
		float squareVertices[4 * 3] = {
			0.0f, -0.08f, 0.0f,
			0.1f, -0.08f, 0.0f,
			0.1f, 0.08f, 0.0f,
			0.0f, 0.08f, 0.0f
		};
		std::shared_ptr<Phoenix::VertexBuffer> vertexBufferSquare;
		vertexBufferSquare.reset(Phoenix::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Phoenix::BufferLayout squareLayout = {
			{ Phoenix::ShaderDataType::Float3, "a_Position" },
		};
		vertexBufferSquare->SetLayout(squareLayout);
		m_VertexArraySquares->AddVertexBuffer(vertexBufferSquare);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Phoenix::IndexBuffer> indexBuffer;
		indexBuffer.reset(Phoenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 0, 3, 2 };
		std::shared_ptr<Phoenix::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(Phoenix::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_VertexArraySquares->SetIndexBuffer(squareIndexBuffer);

		std::string vertexShader = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatShader.reset(Phoenix::Shader::Create(vertexShader, fragmentShader));
    }

    void OnUpdate(Phoenix::Timestep timestamp) override {
		float tsSeconds = timestamp.GetSeconds();
		float tsMilliseconds = timestamp.GetMilliseconds();
		m_FPS = (unsigned int)(1000.0f / tsMilliseconds);
		m_Frametime = tsMilliseconds;

		if (Phoenix::Input::IsKeyPressed(PN_KEY_LEFT)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x - m_CameraSpeed * tsSeconds, m_Camera.GetPosition().y, m_Camera.GetPosition().z });
		}
		if (Phoenix::Input::IsKeyPressed(PN_KEY_RIGHT)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x + m_CameraSpeed * tsSeconds, m_Camera.GetPosition().y, m_Camera.GetPosition().z });
		}
		if (Phoenix::Input::IsKeyPressed(PN_KEY_UP)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x, m_Camera.GetPosition().y + m_CameraSpeed * tsSeconds, m_Camera.GetPosition().z });
		}
		if (Phoenix::Input::IsKeyPressed(PN_KEY_DOWN)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x, m_Camera.GetPosition().y - m_CameraSpeed * tsSeconds, m_Camera.GetPosition().z });
		}

        Phoenix::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
        Phoenix::RenderCommand::Clear();

        Phoenix::Renderer::BeginScene(m_Camera);
		
		std::dynamic_pointer_cast<Phoenix::OpenGLShader>(m_FlatShader)->Bind();

		for (int x = 0; x < 15; ++x) {
			for (int y = 0; y < 15; ++y) {
				if (x % 2) 
					std::dynamic_pointer_cast<Phoenix::OpenGLShader>(m_FlatShader)->SetUniformFloat4(glm::vec4(0.2f, m_ShaderSlider, 0.2f, 1.0f), "u_Color");
				else
					std::dynamic_pointer_cast<Phoenix::OpenGLShader>(m_FlatShader)->SetUniformFloat4(glm::vec4(0.2f, 0.2f, m_ShaderSlider, 1.0f), "u_Color");

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.13f, y * 0.18f, 1.0f));
				Phoenix::Renderer::Submit(m_VertexArraySquares, m_FlatShader, transform);
			}
		}

		std::dynamic_pointer_cast<Phoenix::OpenGLShader>(m_FlatShader)->SetUniformFloat4(glm::vec4(0.8f, 0.2f, m_ShaderSlider, 1.0f), "u_Color");
        Phoenix::Renderer::Submit(m_VertexArray, m_FlatShader);
        Phoenix::Renderer::EndScene();
    }

    void OnEvent(Phoenix::Event& e) override {
		Phoenix::EventDispatcher dispatcher(e);
    }

    void OnImGuiRender() override {
		ImGui::SetNextWindowSize(ImVec2(150, 100), ImGuiCond_FirstUseEver);
		ImGui::Begin("Framerate", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::Text("%d FPS, %.3f ms", m_FPS, m_Frametime);
		ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(300, 100), ImGuiCond_FirstUseEver);
		ImGui::Begin("Shader Color", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::SliderFloat("Color Slider", &m_ShaderSlider, 0.0f, 1.0f);
		ImGui::End();
		//ImGui::ShowDemoWindow();
    }
private:
    std::shared_ptr<Phoenix::Shader> m_FlatShader;
	std::shared_ptr<Phoenix::VertexArray> m_VertexArray;
	std::shared_ptr<Phoenix::VertexArray> m_VertexArraySquares;
    Phoenix::OrthographicCamera m_Camera;
	float m_Frametime = 0.0f;
	unsigned int m_FPS = 0;
	float m_ShaderSlider = 0.0f;

	float m_CameraSpeed = 1.0f;
};

class Sandbox : public Phoenix::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {

    }
};

Phoenix::Application* Phoenix::CreateApplication() {
    return new Sandbox();
}