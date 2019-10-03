#include "Shader.h"
#include <NightFall/rendering/Renderer.h>
#include <NightFall/platform/opengl/OpenGLShader.h>

namespace nfe {

	Shader::~Shader()
	{
	}

	ref<Shader> Shader::create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc, const std::string& name)
	{
		switch (RendererAPI::getAPI()) {
			case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertexShaderSrc, pixelShaderSrc, name);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	ref<Shader> Shader::create(const std::string& filepath)
	{
		switch (RendererAPI::getAPI()) {
		case RendererAPI::API::None: ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
		}
		ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	void ShaderLibrary::add(const std::string& name, const ref<Shader>& shader)
	{
		ASSERT(!exists(name), "Shader already exists!");
		_shaders[name] = shader;
	}
	void ShaderLibrary::add(const ref<Shader>& shader)
	{
		ASSERT(!exists(shader->getName()), "Shader already exists!");
		_shaders[shader->getName()] = shader;
	}
	ref<Shader> ShaderLibrary::load(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}
	ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}
	ref<Shader> ShaderLibrary::get(const std::string& name)
	{
		ASSERT(exists(name), "Shader already exists!");
		return _shaders.at(name);
	}
	bool ShaderLibrary::exists(const std::string& name) const
	{
		return _shaders.find(name) != _shaders.end();
	}
}