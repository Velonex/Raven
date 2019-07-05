#include "Buffer.h"
#include "Renderer.h"
#include <NightFall/utils/Assert.h>
#include <NightFall/platform/opengl/OpenGLBuffer.h>

namespace nfe {

	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI()) {
		case RendererAPI::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::getAPI()) {
		case RendererAPI::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}