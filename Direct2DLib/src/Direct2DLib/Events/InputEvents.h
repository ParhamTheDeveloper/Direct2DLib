#pragma once

#include "Event.h"
#include "Direct2DLib/Math/Vector2.h"

namespace D2DLib
{

	class D2DLIB_API MouseDownEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			MouseDownEvent,
			const Vector2& position = 0.0f,
			bool isRight = false
		)
			Position(position),
			IsRight(isRight)
		{
		}

		EventType GetType() const { return EventType::MouseDown; }
	public:
		Vector2 Position;
		bool IsRight;
	};

	using MouseClickEvent = MouseDownEvent;

	class D2DLIB_API MouseUpEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			MouseUpEvent,
			const Vector2& position = 0.0f,
			bool isRight = false
		)
			Position(position),
			IsRight(isRight)
		{
		}

		EventType GetType() const { return EventType::MouseUp; }
	public:
		Vector2 Position;
		bool IsRight;
	};

	class D2DLIB_API MouseMoveEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			MouseMoveEvent,
			const Vector2& position = 0.0f,
			bool isRight = false
		)
			Position(position),
			IsRight(isRight)
		{
		}

		EventType GetType() const { return EventType::MouseMove; }
	public:
		Vector2 Position;
		bool IsRight;
	};

	class D2DLIB_API KeyDownEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			KeyDownEvent,
			int character
		)
			Character(character)
		{
		}

		EventType GetType() const { return EventType::KeyDown; }
	public:
		int Character;
	};

	class D2DLIB_API KeyUpEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			KeyUpEvent,
			int character
		)
			Character(character)
		{
		}

		EventType GetType() const { return EventType::KeyUp; }
	public:
		int Character;
	};

	class D2DLIB_API KeyPressEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			KeyPressEvent,
			int character
		)
			Character(character)
		{
		}

		EventType GetType() const { return EventType::KeyPress; }
	public:
		int Character;
	};

}