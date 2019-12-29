#include <pch.h>
#include "Texture.h"
#include <Raven/rendering/Renderer.h>
#include <Raven/platform/opengl/OpenGLTexture.h>

namespace rvn {
	ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (RendererAPI::getAPI()) {
			case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(width, height);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	ref<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (RendererAPI::getAPI()) {
			case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(path);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}