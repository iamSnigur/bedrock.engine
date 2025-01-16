#include "Shader.h"
#include "Renderer.h"
#include "OpenGL\OpenGLShader.h"

namespace Bedrock
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		return nullptr;
			case RendererAPI::API::OpenGL:	return new OpenGLShader(filepath);
		}
	}
}