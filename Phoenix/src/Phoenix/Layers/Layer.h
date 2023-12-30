#pragma once

#include "Phoenix/Events/Event.h"

namespace Phoenix {
	class PHOENIX_API Layer {
	public:
		Layer(const std::string& name);
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& e);

		inline const std::string& GetDebugName() const { return m_DebugName; };
	private:
		std::string m_DebugName;
	};
}
