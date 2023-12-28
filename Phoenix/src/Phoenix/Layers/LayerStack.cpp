#include "pnpch.h"
#include "LayerStack.h"

namespace Phoenix {
	LayerStack::LayerStack() {
		m_LayerInsertIndex = -1;
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		if (m_Layers.size() == 0) {
			m_Layers.emplace_back(layer);
		}
		else {
			std::vector<Layer*>::iterator iter = m_Layers.begin() + m_LayerInsertIndex + 1;
			if (iter != m_Layers.end()) {
				m_Layers.emplace(iter, layer);
			}
		}
		++m_LayerInsertIndex;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		if (m_LayerInsertIndex >= 0) {
			std::vector<Layer*>::iterator iter = m_Layers.begin() + m_LayerInsertIndex;
			m_Layers.erase(iter);
			--m_LayerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		std::vector<Layer*>::iterator iter = m_Layers.begin() + m_LayerInsertIndex + 1;
		if (iter != m_Layers.end()) {
			m_Layers.pop_back();
		}
	}
}