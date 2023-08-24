#pragma once

#include "Event.h"

namespace D2DLib
{

	class WindowResizeEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			WindowResizeEvent,
			float width = 0.0f, float height = 0.0f
		)
			Width(width), Height(height)
		{
		}

		EventType GetType() const { return EventType::WindowResize; }
	public:
		float Width, Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			WindowCloseEvent,
			UInt exitCode
		)
			ExitCode(exitCode)
		{
		}

		EventType GetType() const { return EventType::WindowClose; }
	public:
		UInt ExitCode;
	};

	class WindowUpdateEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			WindowUpdateEvent,
			float deltaTime = 0.0f
		)
			DeltaTime(deltaTime)
		{
		}

		EventType GetType() const { return EventType::WindowUpdate; }
	public:
		float DeltaTime;
	};

	class WindowTimerEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			WindowTimerEvent,
			UInt timerId = 0
		)
			TimerId(timerId)
		{
		}

		EventType GetType() const { return EventType::WindowTimer; }
	public:
		UInt64 TimerId;
	};

}