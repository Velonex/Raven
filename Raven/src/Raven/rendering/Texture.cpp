#include "Texture.h"
#include <Raven/rendering/Renderer.h>
#include <Raven/platform/opengl/OpenGLTexture.h>

namespace rvn {
	ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (RendererAPI::getAPI()) {
		case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}