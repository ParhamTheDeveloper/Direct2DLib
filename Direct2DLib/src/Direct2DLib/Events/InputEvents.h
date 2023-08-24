#pragma once

#include "Event.h"
#include "Direct2DLib/Math/Vector2.h"

namespace D2DLib
{

	class MouseDownEvent : public Event
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

	class MouseUpEvent : public Event
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

	class MouseMoveEvent : public Event
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

	class KeyDownEvent : public Event
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

	class KeyUpEvent : public Event
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

	class KeyPressEvent : public Event
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