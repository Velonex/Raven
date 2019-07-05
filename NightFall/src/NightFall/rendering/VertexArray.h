#pragma once

#include <NightFall/rendering/Buffer.h>

namespace nfe {

	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void addVertexBuffer(const VertexBuffer* vertexBuffer) = 0;
		virtual void setIndexBuffer(const IndexBuffer* indexBuffer) = 0;

		virtual const std::vector<VertexBuffer*> getVertexBuffers() const = 0;
		virtual const IndexBuffer* getIndexBuffer() const = 0;

		static VertexArray* create();
	};

}