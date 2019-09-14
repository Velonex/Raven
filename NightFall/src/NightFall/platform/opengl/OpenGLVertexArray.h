#pragma once

#include <NightFall/rendering/VertexArray.h>

namespace nfe {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const ref<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<ref<VertexBuffer>> getVertexBuffers() const override;
		virtual const ref<IndexBuffer> getIndexBuffer() const override;
	private:
		std::vector<ref<VertexBuffer>> _vertexBuffers;
		ref<IndexBuffer> _indexBuffer;
		uint32_t _uid;
	};

}