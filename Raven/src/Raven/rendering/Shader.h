#pragma once

#include <glm.hpp>
#include <Raven/core/Core.h>
#include <unordered_map>

namespace rvn {

	class Shader {
	public:
		virtual ~Shader();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const std::string& getName() const = 0;

		static ref<Shader> create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc, const std::string& name);
		static ref<Shader> create(const std::string& filepath);

		// Uniforms
		virtual void setInt(const std::string& name, int value) = 0;
		virtual void setFloat(const std::string& name, float value) = 0;
		virtual void setFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void setMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void setMat4(const std::string& name, const glm::mat4& value) = 0;
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