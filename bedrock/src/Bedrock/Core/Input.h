#pragma once

#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

namespace Bedrock
{
	class Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static glm::vec2 GetMousePosition();

	private:
		static GLFWwindow* GetGLFWWindow();
	};
}