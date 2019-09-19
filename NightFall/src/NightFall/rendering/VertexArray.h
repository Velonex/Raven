#pragma once

#include <NightFall/rendering/Buffer.h>
#include <NightFall/core/Core.h>
#include <stb_image.h>

namespace nfe {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<ref<VertexBuffer>> getVertexBuffers() const = 0;
		virtual const ref<IndexBuffer> getIndexBuffer() const = 0;

		static VertexArray* create();
	};

}