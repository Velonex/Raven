#pragma once
#include <NightFall/rendering/Buffer.h>

namespace nfe {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void setLayout(const BufferLayout& layout) override;
		virtual const BufferLayout& getLayout() const { return _layout; }
		~OpenGLVertexBuffer();
	private:
		uint32_t _id;
		BufferLayout _layout;
	};
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual void bind() const override;
		virtual void unbind() const override;
		~OpenGLIndexBuffer();
	private:
		uint32_t _id;
	};
}