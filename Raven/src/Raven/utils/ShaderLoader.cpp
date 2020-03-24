#include <pch.h>
#include "ShaderLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Assert.h"

namespace rvn {
	std::unordered_map<std::string, std::string> ShaderLoader::readShaderFile(const std::string& filepath)
	{
		std::unordered_map<std::string, std::string> sources;
		std::string content;
		content = readFile(filepath);
		sources = parseSource(content);
		return sources;
	}
	std::string ShaderLoader::readFile(const std::string& filepath)
	{
		std::string file;
		std::ifstream in(filepath, std::ios::ate || std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			size_t length = in.tellg();
			if (length != -1) {
				file.resize(length);
				in.seekg(0, std::ios::beg);
				in.read(&file[0], length);
				in.close();
			}
			else {
				LOG_ENGINE_ERROR("Couldn't read shader file \'{0}\'", filepath);
			}
		}
		else {
			LOG_ENGINE_ERROR("Couldn't open shader file \'{0}\'", filepath);
		}
		return file;
	}
	std::vector<std::string> split(std::string const& str, const std::string& delim)
	{
		std::vector<std::string> out;
		size_t start;
		size_t end = 0;

		while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = str.find(delim, start);
			out.push_back(str.substr(start, end - start));
		}
		return out;
	}
	std::unordered_map<std::string, std::string> ShaderLoader::parseSource(const std::string& source)
	{
		std::unordered_map<std::string, std::string> sources;
		const char* token = "#type ";
		std::vector<std::string> vec = split(source, token);
		ASSERT(vec.size() == 1, "Syntax error");
		if (source.find("#type ") != 0) {
			vec.erase(vec.begin());
		}
		for (std::string s : vec) {
			size_t end = s.find_first_of("\r\n	");
			sources[s.substr(0, end)] = s.substr(end, s.length());
		}
		return sources;
	}
}