#pragma once

#include <vector>
#include <memory>

#include "Window.h"
#include "Layers/Layer.h"
#include "Events/EventDispatcher.h"

namespace Bedrock
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Boot();
		void Run();

		void OnEventCallback(Event& e);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool m_IsRunning{ false };
		float m_LastFrameTime{ 0.0f };
		std::vector<Layer*> m_Layers;
		std::unique_ptr<Window> m_Window;
		EventDispatcher m_EventDispatcher;

		void OnWindowClose(WindowCloseEvent& e);
		void OnCursorMove(CursorMoveEvent& e);

		void PushLayer(Layer* layer);

		static Application* s_Instance;
	};
}