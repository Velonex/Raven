#include "Shader.h"
#include <NightFall/rendering/Renderer.h>
#include <NightFall/platform/opengl/OpenGLShader.h>

namespace nfe {

	Shader::~Shader()
	{
	}

	ref<Shader> Shader::create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc)
	{
		switch (RendererAPI::getAPI()) {
			case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertexShaderSrc, pixelShaderSrc);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	void ShaderLibrary::add(const std::string& name, const ref<Shader>& shader)
	{
		//ASSERT(!exists(name), "Shader already exists!");
		_shaders[name] = shader;
	}
	ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		//ASSERT(exists(name), "Shader already exists!");
		return _shaders.at(name);
	}
	bool ShaderLibrary::exists(const std::string& name) const
	{
		return _shaders.find(name) != _shaders.end();
	}
}