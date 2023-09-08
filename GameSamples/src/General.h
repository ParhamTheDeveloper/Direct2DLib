#pragma once

#include <Direct2DLib/Direct2DLib.h>

using namespace D2DLib;

class GameApplication : public Application
{
public:
	GameApplication(const String& title, UInt width, UInt height)
		: Application(title, width, height)
	{
		SetVSync(true);
	}

	void InitializeEvents() override
	{
		m_Window->AddListener<WindowResizeEvent>(EventType::WindowResize, BindEventCallback(&GameApplication::OnWindowResize, this));
	}

	void OnWindowResize(const WindowResizeEvent& e)
	{
		InitializeResources();
	}

	void InitializeResources() override
	{

	}

	void UninitializeResources() override
	{
		
	}

	void InitializeFrameResources() override
	{
		m_RectStyle = RectangleStyle(100.0f, 100.0f, 10.0f,
			CreateBrush(Color(155.0f, 55.0f, 200.0f)));
	}

	void UninitializeFrameResources() override
	{
		m_RectStyle.BackgroundColor.Release();
	}

	void Render(DeltaTime deltaTime)
	{
		DrawRectangle(m_RectStyle);
	}
private:
	RectangleStyle m_RectStyle;
};