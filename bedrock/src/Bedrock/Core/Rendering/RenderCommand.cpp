#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Bedrock
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}