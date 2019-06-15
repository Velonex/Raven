#include "Renderer.h"
#include <NightFall/platform/opengl/OpenGLRenderer.h>
#include <NightFall/utils/Assert.h>
#include <glad/glad.h>


namespace nfe {
	RendererAPI Renderer::s_rendererAPI = RendererAPI::OpenGL;
	void Renderer::setClearColorRGBA(float r, float g, float b, float a)
	{
		switch (getAPI()) {
			case RendererAPI::None: ASSERT(false, "RendererAPI::None is currently not supported"); return;
			case RendererAPI::OpenGL: OpenGLRenderer::setClearColorRGBA(r, g, b, a); return;
		}
		ASSERT(false, "Unknown RendererAPI")
		return;
	}
}