#pragma once

#include <NightFall/rendering/Shader.h>

namespace nfe {

	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc);
		virtual ~OpenGLShader();

		virtual void bind() const override;
		virtual void unbind() const override;

		void uploadUniformInt(const std::string& name, int value) const;

		void uploadUniformFloat(const std::string& name, float value) const;
		void uploadUniformFloat2(const std::string& name, const glm::vec2& value) const;
		void uploadUniformFloat3(const std::string& name, const glm::vec3& value) const;
		void uploadUniformFloat4(const std::string& name, const glm::vec4& value) const;

		void uploadUniformMat3(const std::string& name, const glm::mat3& value) const;
		void uploadUniformMat4(const std::string& name, const glm::mat4& value) const;
	private:
		uint32_t _programId;
	};

}