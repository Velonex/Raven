#pragma once

#include <NightFall/rendering/VertexArray.h>

namespace nfe {

	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void addVertexBuffer(const VertexBuffer* vertexBuffer) override;
		virtual void setIndexBuffer(const IndexBuffer* indexBuffer) override;

		virtual const std::vector<VertexBuffer*> getVertexBuffers() const override;
		virtual const IndexBuffer* getIndexBuffer() const override;
	private:
		std::vector<VertexBuffer*> _vertexBuffers;
		IndexBuffer* _indexBuffer;
		uint32_t _uid;
	};

}