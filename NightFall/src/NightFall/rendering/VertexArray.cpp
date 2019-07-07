#include "VertexArray.h"

#include <NightFall/rendering/Renderer.h>
#include <NightFall/platform/opengl/OpenGLVertexArray.h>

namespace nfe {

	VertexArray* nfe::VertexArray::create()
	{
		switch (RendererAPI::getAPI()) {
		case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}