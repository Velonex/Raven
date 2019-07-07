#pragma once

#include <string>
#include <glm.hpp>

namespace nfe {

	class Shader {
	public:
		Shader(std::string vertexShaderSrc, std::string pixelShaderSrc);
		~Shader();
		
		void bind() const;
		void unbind() const;

		void uploadUniformMat4(const char* name, const glm::mat4& mat) const;
	private:
		uint32_t _programId;
	};

}