#pragma once

#include <string>
#include <glm.hpp>
#include <NightFall/core/Core.h>
#include <unordered_map>

namespace nfe {

	class Shader {
	public:
		virtual ~Shader();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& getName() const = 0;

		static ref<Shader> create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc, const std::string& name);
		static ref<Shader> create(const std::string& filepath);
	};
	class ShaderLibrary {
	public:
		void add(const std::string& name, const ref<Shader>& shader);
		void add(const ref<Shader>& shader);

		ref<Shader> load(const std::string& filepath);
		ref<Shader> load(const std::string& name, const std::string& filepath);

		ref<Shader> get(const std::string& name);

		bool exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, ref<Shader>> _shaders;
	};

}