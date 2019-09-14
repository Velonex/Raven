#pragma once

#include <string>
#include <glm.hpp>

namespace nfe {

	class Shader {
	public:
		virtual ~Shader();
		
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Shader* create(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc);
	};

}