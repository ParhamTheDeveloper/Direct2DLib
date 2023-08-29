#pragma once

#include "Direct2DLib/Core/Base.h"
#include "Direct2DLib/Core/Forwards.h"
#include "Utils.h"

#define D2DLIB_DECLARE_EVENT_CTOR(eventName, ...)		\
	eventName(											\
		Window& target,									\
		HWND hwnd, UInt uMsg,							\
		UInt64 wParam, UInt64 lParam,					\
		##__VA_ARGS__									\
	) :													\
		Event(											\
			target,										\
			hwnd, uMsg,									\
			wParam, lParam								\
		),

namespace D2DLib
{

	enum class D2DLIB_API EventType
	{
		None,
		WindowClose, WindowResize, WindowUpdate, WindowTimer,
		MouseDown, MouseUp, MouseMove, MouseClick = MouseDown,
		KeyDown, KeyUp, KeyPress,
		ApplicationRender
	};

	class D2DLIB_API Event
	{
	public:
		Event(
			Window& target,
			HWND hwnd = nullptr,
			UInt uMsg = WM_NULL,
			UInt64 param = 0,
			UInt64 data = 0
		)
			:
			Target(target),
			HWnd(hwnd),
			Message(uMsg),
			Param(param),
			Data(data)
		{
		}

		virtual EventType GetType() const { return EventType::None; }

		template<typename DerivedEvent>
		DerivedEvent Get() const
		{
			Scoped<Event> scopedThis = CreateScoped<Event>(*this);
			return static_cast<DerivedEvent&>(*scopedThis);
		}
	public:
		HWND HWnd;
		UInt Message; // // A general name for uMsg
		UInt64 Param; // A general name for wParam
		UInt64 Data; // A general name for lParam
		Window& Target;
	};

}