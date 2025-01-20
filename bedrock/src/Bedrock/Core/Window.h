#pragma once

#include <string>
#include <functional>

#include "GLFW\glfw3.h"
#include "Rendering\RenderingContext.h"
#include "Events\Event.h"

namespace Bedrock
{
	using EventCallback_func = std::function<void(Event&)>;

	class Window
	{
	public:
		Window(int width, int height, const std::string& title);
		~Window();

		void SetEventCallback(const EventCallback_func& callback);
		void EnableVSync(bool enable = true);
		void SetCursorDisabled();
		void SetCursorNormal();
		void OnUpdate();

		inline void* GetNativeWindow() { return m_Window; }

	private:
		GLFWwindow* m_Window;
		RenderingContext* m_Context;

		EventCallback_func m_EventCallback;
	};
}