#include "EventDispatcher.h"

namespace Bedrock
{
	EventDispatcher::EventDispatcher()
	{
	}

	void EventDispatcher::Dispatch(Event& e)
	{
		switch (e.GetType())
		{
		case EventType::WindowClose:
			if (m_OnWindowCloseCallback)
				m_OnWindowCloseCallback(static_cast<WindowCloseEvent&>(e));
			break;
		case EventType::WindowResize:
			break;
		case EventType::KeyPress:
			if (m_OnKeyPressCallback)
				m_OnKeyPressCallback(static_cast<KeyPressEvent&>(e));
			break;
		case EventType::KeyHold:
			break;
		case EventType::KeyRelease:
			break;
		case EventType::CursorMove:
			if (m_OnCursorMoveCallback)
				m_OnCursorMoveCallback(static_cast<CursorMoveEvent&>(e));
			break;
		default:
			break;
		}
	}

	// cache callbacks in map
	void EventDispatcher::SetWindowCloseCallback(const OnWindowCloseCallback_func& callback)
	{
		m_OnWindowCloseCallback = callback;
	}

	void EventDispatcher::SetCursorMoveCallback(const OnCursorMoveCallback_func& callback)
	{
		m_OnCursorMoveCallback = callback;
	}

	void EventDispatcher::SetKeyPressCallback(const OnKeyPressCallback_func& callback)
	{
		m_OnKeyPressCallback = callback;
	}
}