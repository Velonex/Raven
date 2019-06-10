#pragma once

#include <string>

namespace nfe {

	class Shader {
	public:
		Shader(std::string vertexShaderSrc, std::string pixelShaderSrc);
		~Shader();
		void bind();
		void unbind();
	private:
		uint32_t _programId;
	};

}