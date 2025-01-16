#pragma once

#include <functional>
#include <unordered_map>

#include "Event.h"

namespace Bedrock
{
	using OnWindowCloseCallback_func = std::function<void(WindowCloseEvent&)>;
	using OnCursorMoveCallback_func = std::function<void(CursorMoveEvent&)>;
	using OnKeyPressCallback_func = std::function<void(KeyPressEvent&)>;

	class EventDispatcher
	{
	public:
		EventDispatcher();

		void Dispatch(Event& e);

		void SetWindowCloseCallback(const OnWindowCloseCallback_func& callback);
		void SetCursorMoveCallback(const OnCursorMoveCallback_func& callback);
		void SetKeyPressCallback(const OnKeyPressCallback_func& callback);

	private:
		std::unordered_map<EventType, int> _;

		OnWindowCloseCallback_func m_OnWindowCloseCallback;
		OnCursorMoveCallback_func m_OnCursorMoveCallback;
		OnKeyPressCallback_func m_OnKeyPressCallback;

		
	};
}