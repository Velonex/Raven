#ifndef SHADER_H_
#define SHADER_H_

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

#endif