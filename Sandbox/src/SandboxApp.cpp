#include "Phoenix/Phoenix.h"
#include "imgui.h"

class ExampleLayer : public Phoenix::Layer {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f) {
		m_VertexArray.reset(Phoenix::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.4f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Phoenix::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Phoenix::VertexBuffer::Create(vertices, sizeof(vertices)));

		Phoenix::BufferLayout layout = {
			{ Phoenix::ShaderDataType::Float3, "a_Position" },
			{ Phoenix::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Phoenix::IndexBuffer> indexBuffer;
		indexBuffer.reset(Phoenix::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexShader = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShader = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(Phoenix::Shader::Create(vertexShader, fragmentShader));
    }

    void OnUpdate() override {
		if (Phoenix::Input::IsKeyPressed(PN_KEY_LEFT)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x - m_CameraSpeed, m_Camera.GetPosition().y, m_Camera.GetPosition().z });
		}
		if (Phoenix::Input::IsKeyPressed(PN_KEY_RIGHT)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x + m_CameraSpeed, m_Camera.GetPosition().y, m_Camera.GetPosition().z });
		}
		if (Phoenix::Input::IsKeyPressed(PN_KEY_UP)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x, m_Camera.GetPosition().y + m_CameraSpeed, m_Camera.GetPosition().z });
		}
		if (Phoenix::Input::IsKeyPressed(PN_KEY_DOWN)) {
			m_Camera.SetPosition({ m_Camera.GetPosition().x, m_Camera.GetPosition().y - m_CameraSpeed, m_Camera.GetPosition().z });
		}

        Phoenix::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
        Phoenix::RenderCommand::Clear();

        Phoenix::Renderer::BeginScene(m_Camera);

        Phoenix::Renderer::Submit(m_VertexArray, m_Shader);

        Phoenix::Renderer::EndScene();
    }

    void OnEvent(Phoenix::Event& e) override {
		Phoenix::EventDispatcher dispatcher(e);
    }

    void OnImGuiRender() override {

    }
private:
    std::shared_ptr<Phoenix::Shader> m_Shader;
    std::shared_ptr<Phoenix::VertexArray> m_VertexArray;
    Phoenix::OrthographicCamera m_Camera;

	float m_CameraSpeed = 0.02f;
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