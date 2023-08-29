#include "pch.h"
#include "Application.h"

namespace D2DLib
{

	DeltaTime::DeltaTime()
		: m_Time(0.0f)
	{
	}

	DeltaTime::DeltaTime(float deltaTime)
		: m_Time(deltaTime)
	{
	}

	void DeltaTime::Set(float deltaTime)
	{
		m_Time = deltaTime;
	}

	const float& DeltaTime::Get() const { return m_Time; }

	DeltaTime::operator const float& () const { return m_Time; }

	void DeltaTime::operator=(float deltaTime)
	{
		m_Time = deltaTime;
	}

	Application::Application(const String& title, UInt width, UInt height, ApplicationWindowInfo windowInfo)
	{
		// Debug Console settings

		Debug::Console::SetTitle(L"D2DLib Debug Console [" + title + L"]");
		Debug::Console::SetStyle({ 900.0f, 500.0f, { 100.0f, 100.0f } });

		// Window initalization section

		UInt screenWidth = GetSystemMetrics(SM_CXSCREEN);
		UInt screenHeight = GetSystemMetrics(SM_CYSCREEN);
		WindowStyle windowStyle = {
			Cast<float>(width), Cast<float>(height),
			{
				Cast<float>(screenWidth - width) / 2.0f,
				Cast<float>(screenHeight - height) / 2.0f
			},
			windowInfo.BackgroundColor, windowInfo.Maximized
		};
		m_Window = new Window(title, windowStyle);
	}

	Application::~Application()
	{
		SafeRelease(m_Window);
	}

	void Application::SetVSync(bool useVSync)
	{
		m_UseVSync = useVSync;
	}

	bool Application::GetVSync() const { return m_UseVSync; }

	void Application::Run()
	{
		InitializeResources();
		InitializeEvents();

		while (!m_Window->ShouldClose())
		{
			CalculateDeltaTime();
			BaseRender();
		}

		UninitializeResources();
	}

	void Application::InitializeResources()
	{
		Style windowStyle = m_Window->GetClientSize();
		m_TextStyle.Position = Vector2(windowStyle.Width - 30.0f * 8.0f / 2.0f, (windowStyle.Height - 30.0f) / 2.0f);
		m_TextStyle.Color = CreateBrush({ 255.0f, 255.0f, 255.0f });
		m_TextStyle.Font = Font(30.0f, L"Bahnschrift");
	}

	void Application::InitializeEvents()
	{
		m_Window->AddListener<WindowResizeEvent>(EventType::WindowResize,
			BindEventCallback(&Application::OnWindowResize, this));
	}

	void Application::UninitializeResources()
	{
		SafeRelease(&m_TextStyle.Color);
	}

	void Application::CalculateDeltaTime()
	{
		Timestep currentTime;
		m_Time.DeltaTime = currentTime - m_LastFrameTime;
		m_Time.ElapsedTime += m_Time.DeltaTime;
		m_LastFrameTime = currentTime;
	}

	void Application::BaseRender()
	{
		BeginDraw();

		ClearScreen(m_Window->GetStyle().BackgroundColor);
		DispatchRenderEvent();
		Render(m_Time.DeltaTime);

		EndDraw();
		SynchronizeScreen();
	}

	void Application::DispatchRenderEvent()
	{
		Event event(*m_Window, m_Window->GetWindow(), D2DLIB_WM_APPLICATION_RENDER, NULL, NULL);
		ApplicationRenderEvent listenerEvent = event.Get<ApplicationRenderEvent>();
		listenerEvent.DeltaTime = m_Time.DeltaTime;
		m_Window->DispatchEvent(EventType::ApplicationRender, listenerEvent);
	}

	void Application::SynchronizeScreen()
	{
		Sleep(m_UseVSync ? 1000 / GetScreenRefreshRate() : 1);
	}

	void Application::Render(DeltaTime deltaTime)
	{
		RenderText(L"Hello, D2DLib :)", m_TextStyle);
	}

	void Application::OnWindowResize(const WindowResizeEvent& e)
	{
		InitializeResources();
	}

	float Application::GetFps() const
	{
		return 1.0f / m_Time.DeltaTime;
	}

	float Application::GetElapsedTime() const
	{
		return m_Time.ElapsedTime;
	}

	float Application::GetDeltaTime() const
	{
		return m_Time.DeltaTime;
	}

}