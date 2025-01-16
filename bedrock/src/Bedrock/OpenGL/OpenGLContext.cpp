#include <iostream>
#include "glad\glad.h"
#include "OpenGLContext.h"

namespace Bedrock
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window {window}
	{
	}

	void OpenGLContext::Boot()
	{
		glfwMakeContextCurrent(m_Window);

		int glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (glad == 0)
			throw;

		std::cout << "Vendor: " << glGetString(GL_VENDOR) << '\n';
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << '\n';
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}