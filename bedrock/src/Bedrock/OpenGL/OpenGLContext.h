#pragma once

#include "GLFW/glfw3.h"
#include "Core/Rendering/RenderingContext.h"

namespace Bedrock
{
	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		
		virtual void Boot() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}