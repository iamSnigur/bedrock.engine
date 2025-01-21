#pragma once

#include <iostream>

#include "glm/glm.hpp"

namespace Bedrock
{
	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform1i(const std::string& name, int v0) = 0;
		virtual void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;

		static Shader* Create(const std::string& vertexPath, const std::string& fragmentPath);
	};
}
