#include "pch.h"
#include "Application.h"

namespace D2DLib
{

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
		
		// Initalization methods section
		
		InitializeResources();
		InitializeEvents();
	}

	Application::~Application()
	{
		SafeRelease(m_Window);
	}

	void Application::Run()
	{
		InitializeResources();
		while (!m_Window->ShouldClose())
		{
			m_Time.DeltaTime.Calculate();
			BaseRender();
		}
		UninitializeResources();
	}

	void Application::InitializeResources()
	{
		Style windowStyle = m_Window->GetClientSize();
		m_TextStyle = {
			0.0f, 0, { (windowStyle.Width - 30.0f * 8.0f) / 2.0f, (windowStyle.Height - 30.0f) / 2.0f, },
			nullptr, CreateBrush({ 255.0f, 255.0f, 255.0f }), Font(30.0f, L"Bahnschrift")
		};
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

	void Application::BaseRender()
	{
		BeginDraw();

		ClearScreen(m_Window->GetStyle().BackgroundColor);
		DispatchRenderEvent();
		Render(m_Time.DeltaTime);

		EndDraw();
		Sleep(1);
	}

	void Application::DispatchRenderEvent()
	{
		Event event(*m_Window, m_Window->GetWindow(), D2DLIB_WM_APPLICATION_RENDER, NULL, NULL);
		ApplicationRenderEvent listenerEvent = event.Get<ApplicationRenderEvent>();
		listenerEvent.DeltaTime = m_Time.DeltaTime;
		m_Window->DispatchEvent(EventType::ApplicationRender, listenerEvent);
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