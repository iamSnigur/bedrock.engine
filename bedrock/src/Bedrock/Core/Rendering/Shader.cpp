#include "Shader.h"
#include "Renderer.h"
#include "OpenGL/OpenGLShader.h"

namespace Bedrock
{
	Shader* Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexPath, fragmentPath);
		}
	}
}