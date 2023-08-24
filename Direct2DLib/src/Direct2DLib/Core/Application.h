#pragma once

#include "Window.h"
#include "Debug.h"
#include "Direct2DLib/Events/ApplicationEvents.h"

#define D2DLIB_BIND_EVENT_CALLBACK(callback, eventType) [this](const eventType& e) { callback(e); }

namespace D2DLib
{

	class DeltaTime
	{
	public:
		DeltaTime()
			: m_LastFrameTime(), m_DeltaTime(0.0f)
		{
		}

		operator const float& () const
		{
			return Calculate();
		}

		const float& GetDelatTime() const
		{
			return Calculate();
		}

		const float& Calculate() const
		{
			const Timestep currentTime;
			m_DeltaTime = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;
			return m_DeltaTime;
		}
	private:
		mutable Timestep m_LastFrameTime;
		mutable float m_DeltaTime;
	};

	struct ApplicationTime
	{
		DeltaTime DeltaTime;
		float ElapsedTime;
	};

	struct ApplicationWindowInfo
	{
		Color BackgroundColor;
		bool Maximized;
	};

	class Application
	{
	public:
		Application(const String& title, UInt width, UInt height, ApplicationWindowInfo windowInfo = { Color(), false });
		virtual ~Application();
		
		virtual void Run();
		virtual void InitializeResources();
		virtual void UninitializeResources();
		virtual void InitializeEvents();
	private:
		void BaseRender();
		void DispatchRenderEvent();
	protected:
		template<typename CallbackType, typename This>
		auto BindEventCallback(CallbackType&& callbackFn, This self)
		{
			return std::bind(callbackFn, self, std::placeholders::_1);
		}
	protected:
		virtual void Render(DeltaTime deltaTime);
		virtual void OnWindowResize(const WindowResizeEvent& e);
		float GetFps() const;
		float GetElapsedTime() const;
		float GetDeltaTime() const;
	protected:
		String m_Title;
		Window* m_Window;
		ApplicationTime m_Time;
	private:
		TextStyle m_TextStyle;
	};

}