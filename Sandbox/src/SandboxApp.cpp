#include "Phoenix/Phoenix.h"
#include "imgui.h"

class ExampleLayer : public Phoenix::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // PN_CLIENT_INFO("ExampleLayer::OnUpdate");
    }

    void OnEvent(Phoenix::Event& e) override {
        // PN_CLIENT_TRACE("{0}", e);
    }

    void OnImGuiRender() override {
        ImGui::NewFrame();
        ImGui::Begin("Start");
        ImGui::Text("Hello world.");
        ImGui::End();
    }
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