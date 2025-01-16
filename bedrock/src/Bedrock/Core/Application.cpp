#include "Application.h"
#include <iostream>
#include <string>
#include <functional>

#include "Core/Time.h"

#include "Layers/TestScene.h"

namespace Bedrock
{
#define BIND_EVENT(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance;

	Application::Application()
	{
		if (s_Instance != nullptr)
			throw;

		s_Instance = this;

		m_EventDispatcher.SetWindowCloseCallback(BIND_EVENT(OnWindowClose));
		m_EventDispatcher.SetCursorMoveCallback(BIND_EVENT(OnCursorMove));

		m_Window.reset(new Window{ 1920, 1080, "Bedrock App" });
		m_Window->SetEventCallback(BIND_EVENT(OnEventCallback));		
	}

	Application::~Application() 
	{
		for (Layer* layer : m_Layers)
			delete layer;

		m_Layers.clear();
	}

	void Application::Boot()
	{
		PushLayer(new TestScene{});
		m_IsRunning = true;
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			float time = (float)glfwGetTime();
			Time deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_Layers)
				layer->OnUpdate(deltaTime);

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
	}

	void Application::OnEventCallback(Event& e)
	{
		m_EventDispatcher.Dispatch(e);

		for (Layer* layer : m_Layers)
			layer->OnEvent(e);
	}

	void Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
	}

	void Application::OnCursorMove(CursorMoveEvent& e)
	{
		printf("Mouse pos (%d, %d)\n", e.GetX(), e.GetY());
	}

	/*void Application::OnWindowResize(WindowResizeEvent& e)
	{

	}*/
}