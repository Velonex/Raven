#include "Shader.h"
#include <NightFall/rendering/Renderer.h>
#include <NightFall/platform/opengl/OpenGLShader.h>

namespace nfe {

	Shader::~Shader()
	{
	}

	Shader* Shader::create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc)
	{
		switch (RendererAPI::getAPI()) {
			case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexShaderSrc, pixelShaderSrc);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}