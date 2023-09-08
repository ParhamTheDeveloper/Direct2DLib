#pragma once

#include "Window.h"
#include "Debug.h"
#include "DeltaTime.h"
#include "Direct2DLib/Events/ApplicationEvents.h"
#include "Direct2DLib/Transitions/TransitionManager.h"

#define D2DLIB_BIND_EVENT_CALLBACK(callback, eventType) [this](const eventType& e) { callback(e); }

namespace D2DLib
{

	struct D2DLIB_API ApplicationTime
	{
		DeltaTime DeltaTime;
		float ElapsedTime;
	};

	struct D2DLIB_API ApplicationWindowInfo
	{
		Color BackgroundColor;
		bool Maximized;
	};

	class D2DLIB_API Application
	{
	public:
		Application(const String& title, UInt width, UInt height, ApplicationWindowInfo windowInfo = { Color(), false });
		virtual ~Application();
		
		void SetVSync(bool useVSync);
		const bool& GetVSync() const;
		void SetFrameRate(UInt fps);
		const UInt& GetFrameRate() const;
		const UInt GetMaxFrameRate() const;

		virtual void Run();
		virtual void InitializeResources();
		virtual void UninitializeResources();
		virtual void InitializeFrameResources();
		virtual void UninitializeFrameResources();
		virtual void InitializeEvents();
	private:
		void BaseRender();
		void DispatchRenderEvent();
		void SynchronizeScreen();
	protected:
		template<typename CallbackType, typename This>
		auto BindEventCallback(CallbackType&& callbackFn, This self)
		{
			return std::bind(callbackFn, self, std::placeholders::_1);
		}
	protected:
		virtual void Render(DeltaTime deltaTime);
		virtual void OnWindowResize(const WindowResizeEvent& e);
		const UInt GetFps() const;
		float GetElapsedTime() const;
		float GetDeltaTime() const;
	protected:
		String m_Title;
		Window* m_Window;
		ApplicationTime m_Time;
		bool m_UseVSync;
		UInt m_FrameRate;
	private:
		TextStyle m_TextStyle;
	};

}
