#pragma once

namespace Bedrock
{
	enum class EventType
	{
		WindowClose,
		WindowResize,
		KeyPress,
		KeyRelease,
		KeyHold,
		MouseButtonPress,
		MouseButtonRelease,
		CursorMove,
	};

	class Event
	{
	public:
		virtual ~Event() {}

		virtual EventType GetType() const = 0;
	};

	class WindowCloseEvent : public Event
	{
	public:
		inline virtual EventType GetType() const { return EventType::WindowClose; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width{width}, m_Height{height}
		{ }

		inline virtual EventType GetType() const { return EventType::WindowResize; }

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

	private:
		int m_Width;
		int m_Height;
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent(int key, EventType type)
			: m_Key{key}, m_EventType{type}
		{ }

		inline virtual EventType GetType() const { return m_EventType; }

		inline int GetKey() const { return m_Key; }

	private:
		int m_Key;
		EventType m_EventType;
	};

	class KeyPressEvent : public Event
	{
	public:
		KeyPressEvent(int key)
			: m_Key{ key }
		{ }

		inline virtual EventType GetType() const { return EventType::KeyPress; }

		inline int GetKey() const { return m_Key; }

	private:
		int m_Key;
	};

	class KeyReleaseEvent : public Event
	{
	public:
		KeyReleaseEvent(int key, EventType type)
			: m_Key{ key }, m_EventType{ type }
		{ }

		inline virtual EventType GetType() const { return EventType::KeyRelease; }

		inline int GetKey() const { return m_Key; }

	private:
		int m_Key;
		EventType m_EventType;
	};

	class KeyHoldEvent : public Event
	{
	public:
		KeyHoldEvent(int key)
			: m_Key{ key }
		{ }

		inline virtual EventType GetType() const { return EventType::KeyHold; }

		inline int GetKey() const { return m_Key; }

	private:
		int m_Key;
	};

	class MouseButtonPressEvent : public Event
	{
	public:
		MouseButtonPressEvent(int button, int action)
			: m_Button{ button }
		{ }

		inline virtual EventType GetType() const { return EventType::MouseButtonPress; }

		inline int GetButton() const { return m_Button; }

	private:
		int m_Button;
	};

	class MouseButtonReleaseEvent : public Event
	{
	public:
		MouseButtonReleaseEvent(int button, int action)
			: m_Button{ button }
		{ }

		inline virtual EventType GetType() const { return EventType::MouseButtonRelease; }

		inline int GetButton() const { return m_Button; }

	private:
		int m_Button;
	};

	class CursorMoveEvent : public Event
	{
	public:
		CursorMoveEvent(double x, double y)
			:	m_X{ x },
				m_Y{ y }
		{ }

		inline virtual EventType GetType() const { return EventType::CursorMove; }

		inline int GetX() const { return m_X; }
		inline int GetY() const { return m_Y; }

	private:
		double m_X;
		double m_Y;
	};
}