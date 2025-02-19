#include "OpenGLShader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace Bedrock
{
	OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
		:	m_RendererID(0)
	{
		ShaderProgramSource src = ParseShader(vertexPath, fragmentPath);
		m_RendererID = CreateShader(src.VertexSource, src.FragmentSource);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniform1i(const std::string& name, int v)
	{
		glUniform1i(GetUniformLocation(name), v);
	}

	void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	ShaderProgramSource OpenGLShader::ParseShader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSrc = ReadShaderFile(vertexPath);
		std::string fragmentSrc = ReadShaderFile(fragmentPath);

		return ShaderProgramSource{ vertexSrc, fragmentSrc };
	}

	std::string OpenGLShader::ReadShaderFile(const std::string& path)
	{
		std::fstream file{ path };

		std::stringstream ss;
		ss << file.rdbuf();

		file.close();

		return ss.str();
	}

	uint32_t OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		const uint32_t program = glCreateProgram();
		const uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		const uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	uint32_t OpenGLShader::CompileShader(const uint32_t type, const std::string& source)
	{
		const uint32_t id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int isCompiled;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_TRUE)
			return id;

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* msg = static_cast<char*>(_malloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, msg);

		std::cerr << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compilation error!" << '\n';
		std::cerr << "\033[31m" << msg << "\n\033[0m"; // replace logger
		delete msg;

		glDeleteShader(id);

		return 0;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformsCache.contains(name))
			return m_UniformsCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());

		m_UniformsCache[name] = location;

		if (location == -1)
			std::cout << "Warning: uniform '" << name << "' does not exist\n";

		return location;
	}
}