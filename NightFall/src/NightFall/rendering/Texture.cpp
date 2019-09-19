#include "Texture.h"
#include <NightFall/rendering/Renderer.h>
#include <NightFall/platform/opengl/OpenGLTexture.h>

namespace nfe {
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