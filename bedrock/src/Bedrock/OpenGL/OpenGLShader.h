#pragma once

#include "Core\Rendering\Shader.h"

#include <string>
#include <unordered_map>
#include "glm\glm.hpp"

namespace Bedrock
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetUniform1i(const std::string& name, int v0) override;
		virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

	private:
		uint32_t m_RendererID;
		std::string m_Filepath;
		std::unordered_map<std::string, int> m_UniformsCache;

		ShaderProgramSource ParseShader(const std::string& path);
		uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		uint32_t CompileShader(const uint32_t type, const std::string& source);

		int GetUniformLocation(const std::string& name);
	};
}
