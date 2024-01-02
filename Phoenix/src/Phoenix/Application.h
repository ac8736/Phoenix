#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace Phoenix 
{
	class PHOENIX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		static inline Application& GetApplication() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}
