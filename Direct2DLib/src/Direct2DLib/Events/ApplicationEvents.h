#pragma once

#include "Event.h"

namespace D2DLib
{

	class D2DLIB_API ApplicationRenderEvent : public Event
	{
	public:
		D2DLIB_DECLARE_EVENT_CTOR(
			ApplicationRenderEvent,
			float deltaTime = 0.0f
		)
			DeltaTime(deltaTime)
		{
		}

		EventType GetType() const { return EventType::ApplicationRender; }
	public:
		float DeltaTime;
	};

}