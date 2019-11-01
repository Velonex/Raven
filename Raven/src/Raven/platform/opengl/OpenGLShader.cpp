#include "OpenGLShader.h"
#include <vector>
#include <glad/glad.h>
#include <Raven/utils/DebugTools.h>
#include <gtc/type_ptr.hpp>
#include <RavenLib/load/ShaderLoader.h>

namespace rvn {

	OpenGLShader::OpenGLShader(const std::string& vertexShaderSrc, const std::string& pixelShaderSrc, const std::string& name) {
		std::unordered_map<std::string, std::string> source;
		source["vertex"] = vertexShaderSrc;
		source["fragment"] = pixelShaderSrc;
		compileShaders(source);
		_name = name;
	}
	OpenGLShader::OpenGLShader(const std::string& filepath) {
		ShaderLoader loader;
		std::unordered_map<std::string, std::string> strSource = loader.readShaderFile(filepath);
		compileShaders(strSource);
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		_name = filepath.substr(lastSlash, count);
	}
	GLenum shaderTypeByName(const std::string& name) {
		if (name == "vertex")
			return GL_VERTEX_SHADER;
		else if (name == "fragment" || name == "pixel")
			return GL_FRAGMENT_SHADER;

		ASSERT(false, "Unknown shader type");
		return 0;
	}
	void OpenGLShader::compileShaders(std::unordered_map<std::string, std::string> strSource)
	{
		std::unordered_map<GLenum, std::string> source;
		for (std::pair<std::string, std::string> p : strSource) {
			source[shaderTypeByName(p.first)] = p.second;
		}
		GLuint* shaderIDs = new GLuint[source.size()];
		uint32_t counter = 0;
		for (std::pair<GLenum, std::string> sh : source) {
			GLuint shader = glCreateShader(sh.first);
			const GLchar* shaderSource = (GLchar*)sh.second.c_str();
			glShaderSource(shader, 1, &shaderSource, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				LOG_ENGINE_ERROR("{0}", infoLog.data());
				ASSERT(false, "Vertex Shader compilation failed!")
					return;
			}
			shaderIDs[counter] = shader;
			counter++;
		}
		GLuint program = glCreateProgram();

		for (GLuint i = 0; i < counter; i++) {
			glAttachShader(program, shaderIDs[i]);
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (GLuint i = 0; i < counter; i++) {
				glDeleteShader(shaderIDs[i]);
			};

			LOG_ENGINE_ERROR("{0}", infoLog.data());
			ASSERT(false, "Shader linking failed!")
				return;
		}

		for (GLuint i = 0; i < counter; i++) {
			glDeleteShader(shaderIDs[i]);
			glDetachShader(program, shaderIDs[i]);
		};
		_programId = program;
		delete shaderIDs;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(this->_programId);
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(this->_programId);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}
	const std::string & OpenGLShader::getName() const
	{
		return _name;
	}
	void OpenGLShader::uploadUniformInt(const std::string& name, int value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniform1i(i, value);
	}
	void OpenGLShader::uploadUniformFloat(const std::string& name, float value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniform1f(i, value);
	}
	void OpenGLShader::uploadUniformFloat2(const std::string& name, const glm::vec2& value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniform2f(i, value.x, value.y);
	}
	void OpenGLShader::uploadUniformFloat3(const std::string& name, const glm::vec3& value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniform3f(i, value.x, value.y, value.z);
	}
	void OpenGLShader::uploadUniformFloat4(const std::string& name, const glm::vec4& value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniform4f(i, value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::uploadUniformMat3(const std::string& name, const glm::mat3& value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniformMatrix3fv(i, 1, false, glm::value_ptr(value));
	}
	void OpenGLShader::uploadUniformMat4(const std::string& name, const glm::mat4& value) const
	{
		int i = glGetUniformLocation(this->_programId, name.c_str());
		glUniformMatrix4fv(i, 1, false, glm::value_ptr(value));
	}
	void OpenGLShader::setInt(const std::string & name, int value)
	{
		uploadUniformInt(name, value);
	}
	void OpenGLShader::setFloat3(const std::string & name, const glm::vec3 & value)
	{
		uploadUniformFloat3(name, value);
	}
	void OpenGLShader::setFloat4(const std::string & name, const glm::vec4 & value)
	{
		uploadUniformFloat4(name, value);
	}
	void OpenGLShader::setMat3(const std::string & name, const glm::mat3 & value)
	{
		uploadUniformMat3(name, value);
	}
	void OpenGLShader::setMat4(const std::string & name, const glm::mat4 & value)
	{
		uploadUniformMat4(name, value);
	}
}