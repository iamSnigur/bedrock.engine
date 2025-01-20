#include "Window.h"

#include "OpenGL\OpenGLContext.h"
#include "Events\Event.h"

namespace Bedrock
{
	static bool s_GLFWInitialized = false;

	static void OnResized(GLFWwindow* window, int width, int height)
	{
		WindowResizeEvent e{ width, height };

		EventCallback_func& cb = *(EventCallback_func*)glfwGetWindowUserPointer(window);
		cb(e);
	}

	static void OnClosed(GLFWwindow* window)
	{
		WindowCloseEvent e{};

		EventCallback_func& cb = *(EventCallback_func*)glfwGetWindowUserPointer(window);
		cb(e);
	}

	static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		EventCallback_func& cb = *(EventCallback_func*)glfwGetWindowUserPointer(window);

		switch (action)
		{
			case GLFW_PRESS:
			{
				KeyPressEvent e{ key };
				cb(e);
				break;
			}
			case GLFW_RELEASE:
				break;
			case GLFW_REPEAT:
				break;
		}
	}

	static void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		MouseButtonReleaseEvent e{ button, action };

		EventCallback_func& cb = *(EventCallback_func*)glfwGetWindowUserPointer(window);
		cb(e);
	}

	static void OnCursorMove(GLFWwindow* window, double x, double y)
	{
		CursorMoveEvent e{ x, y };

		EventCallback_func& cb = *(EventCallback_func*)glfwGetWindowUserPointer(window);
		cb(e);
	}

	static bool InitGLFW()
	{
		if (s_GLFWInitialized)
			return true;

		if (!glfwInit())
			return false;

		/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
		s_GLFWInitialized = true;

		return true;
	}

	Window::Window(int width, int height, const std::string& title)
		: m_Window{ nullptr },
		m_Context{ nullptr },
		m_EventCallback{ nullptr }
	{
		if (!InitGLFW())
			return;

		m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Boot();

		glfwSetKeyCallback(m_Window, OnKey);
		glfwSetWindowSizeCallback(m_Window, OnResized);
		glfwSetWindowCloseCallback(m_Window, OnClosed);
		glfwSetMouseButtonCallback(m_Window, OnMouseButton);
		glfwSetCursorPosCallback(m_Window, OnCursorMove);

		glfwSetWindowUserPointer(m_Window, &m_EventCallback);

		EnableVSync();
	}

	Window::~Window()
	{
		glfwTerminate();

		delete m_Context;
		glfwDestroyWindow(m_Window);
	}

	void Window::SetEventCallback(const EventCallback_func& callback)
	{
		m_EventCallback = callback;
	}

	void Window::EnableVSync(bool enable)
	{
		glfwSwapInterval(enable);
	}

	void Window::SetCursorDisabled()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Window::SetCursorNormal()
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}
}