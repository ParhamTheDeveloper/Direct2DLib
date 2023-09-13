#pragma once

#include "Direct2DLib/Events/MessageManager.h"
#include "Direct2DLib/Events/WindowEvents.h"
#include "Direct2DLib/Events/InputEvents.h"
#include "Direct2DLib/Events/EventListener.h"
#include "Direct2DLib/Input/Input.h"
#include "Direct2DLib/Renderer/Renderer.h"
#include "Direct2DLib/Renderer/RendererGlobal.h"
#include "Direct2DLib/Renderer/ResourceManager.h"
#include "Direct2DLib/Renderer/ResourceManagerGlobal.h"

#define D2DLIB_IMPLEMENT_EVENT_LISTENER(eventName, eventType, ...)		\
	eventName listenerEvent = event.Get<eventName>();					\
	##__VA_ARGS__														\
	DispatchEvent(EventType::eventType, listenerEvent);

namespace D2DLib
{

	class D2DLIB_API Window :
		public MessageManager<Window>,
		public EventListener,
		public Input::Mouse,
		public Input::Keyboard
	{
	public:
		Window(const String& title, const WindowStyle& style);
		~Window();

		bool ShouldClose();
		void Update();
		void SetStyle(const WindowStyle& style);
		void SetIcon(const String& filePath);

		const WindowStyle& GetStyle() const { return m_Style; }
		const wchar_t* GetWindowClassName() const { return L"D2DLib Window"; }
		Graphics* GetGraphics() const { return m_Gfx.get(); }

		const Style GetClientSize();

		void Maximize();
		void Minimize();
		void Restore();

		void CreateTimer(
			bool canUpdate = false,
			UInt64 timerId = 1,
			UInt frameRate = 60,
			const Function<void(const WindowTimerEvent&)>& callbackFn = [](const WindowTimerEvent&) -> void { }
		);
		void DestroyTimer(UInt64 timerId);

		// Window events

		void OnPaint(Event& event);
		void OnResize(Event& event);
		void OnClose(Event& event);
		void OnTimer(Event& event);

		// Mouse events

		void OnMouseDown(Event& event) override;
		void OnMouseUp(Event& event) override;
		void OnMouseMove(Event& event) override;

		// Keyboard events

		void OnKeyDown(Event& event) override;
		void OnKeyUp(Event& event) override;
		void OnKeyPress(Event& event) override;

		D2DLIB_BEGIN_MSG_MAP
			// Window Events

			D2DLIB_HANDLE_MSG(WM_PAINT, OnPaint)
			D2DLIB_HANDLE_MSG(WM_SIZE, OnResize)
			D2DLIB_HANDLE_MSG(WM_DESTROY, OnClose)
			D2DLIB_HANDLE_MSG(WM_TIMER, OnTimer)
			
			// Mouse Events
			// Left button

			D2DLIB_HANDLE_MSG(WM_LBUTTONDOWN, OnMouseDown)
			D2DLIB_HANDLE_MSG(WM_LBUTTONUP, OnMouseUp)

			// Right Button

			D2DLIB_HANDLE_MSG(WM_RBUTTONDOWN, OnMouseDown)
			D2DLIB_HANDLE_MSG(WM_RBUTTONUP, OnMouseUp)

			D2DLIB_HANDLE_MSG(WM_MOUSEMOVE, OnMouseMove)
			
			// Keyboard Events

			D2DLIB_HANDLE_MSG(WM_KEYDOWN, OnKeyDown)
			D2DLIB_HANDLE_MSG(WM_KEYUP, OnKeyUp)
			D2DLIB_HANDLE_MSG(WM_CHAR, OnKeyPress)
		D2DLIB_END_MSG_MAP
	private:
		WindowStyle m_Style;
		Scoped<Graphics> m_Gfx;
		Map<UInt64, Function<void(const WindowTimerEvent&)>> m_Timers;
		static Window* s_Instance;
	private:
		friend D2DLIB_API Window* GetMainWindow();
	};

	D2DLIB_API Window* GetMainWindow();

}