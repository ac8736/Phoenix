#pragma once

#include "Phoenix/Core.h"
#include <Phoenix/Layers/Layer.h>

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
		float m_DeltaTime = 0.0f;
	};
}