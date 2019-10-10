#pragma once

#include <unordered_map>
#include <string>

namespace rvn {

	class ShaderLoader {
	public:
		std::unordered_map<std::string, std::string> readShaderFile(const std::string& filepath);
	private:
		std::unordered_map<std::string, std::string> _shaderFiles;
		std::string readFile(const std::string& filepath);
		std::unordered_map<std::string, std::string> parseSource(const std::string& source);
	};

}