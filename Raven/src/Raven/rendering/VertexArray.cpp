#include <pch.h>
#include "VertexArray.h"

#include <Raven/rendering/Renderer.h>
#include <Raven/platform/opengl/OpenGLVertexArray.h>

namespace rvn {

	ref<VertexArray> rvn::VertexArray::create()
	{
		switch (RendererAPI::getAPI()) {
		case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return createRef<OpenGLVertexArray>();
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}