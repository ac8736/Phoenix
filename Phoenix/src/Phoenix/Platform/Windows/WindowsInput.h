#pragma once

#include "Phoenix/Input.h"

namespace Phoenix {
	class PHOENIX_API WindowsInput : public Input {
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMousePressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}