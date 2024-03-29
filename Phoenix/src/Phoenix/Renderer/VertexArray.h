#pragma once

#include <memory>
#include "Phoenix/Renderer/Buffer.h"

namespace Phoenix {
	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& vertexBuffer) = 0;

		virtual const Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}