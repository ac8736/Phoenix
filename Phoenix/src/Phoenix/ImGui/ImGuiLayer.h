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

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_DeltaTime = 0.0f;
	};
}