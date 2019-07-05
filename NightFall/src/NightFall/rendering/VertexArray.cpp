#include "VertexArray.h"

#include <NightFall/rendering/Renderer.h>
#include <NightFall/platform/opengl/OpenGLVertexArray.h>

namespace nfe {

	VertexArray* nfe::VertexArray::create()
	{
		switch (Renderer::getAPI()) {
		case RendererAPI::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}