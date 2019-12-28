#include "ShaderLoader.h"
#include <fstream>
#include <iostream>
#include <RavenLib/utils/LibAssert.h>
#include <sstream>
#include <string>

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
				LOG_LIB_ERROR("Couldn't read shader file \'{0}\'", filepath);
			}
		}
		else {
			LOG_LIB_ERROR("Couldn't open shader file \'{0}\'", filepath);
		}
		return file;
	}

	std::vector<std::string> split(const std::string& source, const std::string& del)
	{
		std::vector<std::string> ret;
		size_t pos = source.find(del, 0);
		if (pos == std::string::npos) {
			ret.push_back(source);
			return ret;
		}
		size_t next = 0;
		if (pos != std::string::npos)
			next = source.find(del, pos + 1);
		else
			next = source.length();
		if (pos != 0) {
			ret.push_back(source.substr(0, pos));
			pos = 0;
		}
		else {
			size_t split_start = del.length();
			ret.push_back(source.substr(split_start, next - del.length()));
		}
		if (next == std::string::npos) {
			pos = source.find(del);
			ret.push_back(source.substr(pos + del.length(), source.length()));
		}
		while (next != std::string::npos) {
			pos = source.find(del, pos + 1);
			if (pos == std::string::npos) next = source.find(del, pos + 1);
			else next = source.length();
			next = source.find(del, pos + 1);
			ret.push_back(source.substr(pos + del.length(), next - (pos + del.length())));
		}
		return ret;
	}
	std::unordered_map<std::string, std::string> ShaderLoader::parseSource(const std::string& source)
	{
		std::unordered_map<std::string, std::string> sources;
		const char* token = "#type ";
		std::vector<std::string> vec = split(source, token);
		LIB_ASSERT(vec.size() != 1, "Syntax error");
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