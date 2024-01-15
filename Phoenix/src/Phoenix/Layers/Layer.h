#pragma once

#include "Phoenix/Core/Timestep.h"
#include "Phoenix/Events/Event.h"

namespace Phoenix {
	class PHOENIX_API Layer {
	public:
		Layer(const std::string& name);
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(Timestep ts);
		virtual void OnImGuiRender();
		virtual void OnEvent(Event& e);

		inline const std::string& GetDebugName() const { return m_DebugName; };
	private:
		std::string m_DebugName;
	};
}
