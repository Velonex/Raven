#pragma once

#include <Raven/rendering/Shader.h>

namespace rvn {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc, const std::string& name);
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const std::string& getName() const override;

		void uploadUniformInt(const std::string& name, int value) const;

		void uploadUniformFloat(const std::string& name, float value) const;
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value) const;

		void uploadUniformMat3(const std::string& name, const glm::mat3& value) const;
		void uploadUniformMat4(const std::string& name, const glm::mat4& value) const;

		virtual void setFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void setFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void setMat3(const std::string& name, const glm::mat3& value) override;
		virtual void setMat4(const std::string& name, const glm::mat4& value) override;
	private:
		void compileShaders(std::unordered_map<std::string, std::string> strSource);
	private:
		uint32_t _programId;
		std::string _name;
	};

}