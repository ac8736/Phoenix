#pragma once

#include "Phoenix/Core.h"
#include <Phoenix/Layers/Layer.h>

#include <Phoenix/Events/MouseEvent.h>
#include <Phoenix/Events/KeyEvent.h>
#include <Phoenix/Events/ApplicationEvent.h>

namespace Phoenix {
	class PHOENIX_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& e);

	private:
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);

		float m_DeltaTime = 0.0f;
	};
}