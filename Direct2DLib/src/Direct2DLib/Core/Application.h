#pragma once

#include "Window.h"
#include "Debug.h"
#include "Direct2DLib/Events/ApplicationEvents.h"

#define D2DLIB_BIND_EVENT_CALLBACK(callback, eventType) [this](const eventType& e) { callback(e); }

namespace D2DLib
{

	class D2DLIB_API DeltaTime
	{
	public:
		DeltaTime();
		DeltaTime(float deltaTime);

		const float& Get() const;
		operator const float& () const;
	private:
		void Set(float deltaTime);
		void operator=(float deltaTime);
	private:
		float m_Time;
		friend class Application;
	};

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
		bool GetVSync() const;
		virtual void Run();
		virtual void InitializeResources();
		virtual void UninitializeResources();
		virtual void InitializeEvents();
	private:
		void CalculateDeltaTime();
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
		float GetFps() const;
		float GetElapsedTime() const;
		float GetDeltaTime() const;
	protected:
		String m_Title;
		Window* m_Window;
		ApplicationTime m_Time;
		bool m_UseVSync;
	private:
		TextStyle m_TextStyle;
		Timestep m_LastFrameTime;
	};

}
