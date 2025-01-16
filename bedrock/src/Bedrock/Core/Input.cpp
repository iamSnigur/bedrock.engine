#include "Input.h"
#include "Application.h"

namespace Bedrock
{
	bool Input::IsKeyPressed(int keycode)
	{
		GLFWwindow* window = GetGLFWWindow();
		int state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		GLFWwindow* window = GetGLFWWindow();
		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		GLFWwindow* window = GetGLFWWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return glm::vec2((float)xpos, (float)ypos);
	}

	GLFWwindow* Input::GetGLFWWindow()
	{
		return static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	}
}