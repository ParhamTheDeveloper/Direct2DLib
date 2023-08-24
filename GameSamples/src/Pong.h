/*
	Note: This sample game uses an realy old version of D2DLib.
	For better approach making games with D2DLib look at the Pong.h header file.
*/
#pragma once

#include "Direct2DLib/Direct2DLib.h"

using namespace D2DLib;

struct GameState
{
	float PaddleWidth = 0.0f;
	float PaddleHeight = 0.0f;
	float PaddleDistanceX = 0.0f;
	float PaddleDistanceY = 0.0f;
	float BallWidth = 0.0f;
	float BallHeight = 0.0f;
	float BallDistanceX = 0.0f;
	float BallDistanceY = 0.0f;
	float BallMovementTimeX = 0.0f;
	float BallMovementTimeY = 0.0f;
	ShapeStyle LeftPaddle, RightPaddle, Ball;
	Timestep LastFrameTime;
	float ElapsedTime = 0.0f;
	float DeltaTime = 0.0f;
	float WindowWidth = 0.0f;
	float WindowHeight = 0.0f;
	UInt64 FirstPlayerScore = 0;
	UInt64 SecondPlayerScore = 0;
};

class GameApplication : public Application
{
public:
	GameApplication(const String& title, UInt width, UInt height)
		: Application(title, width, height, { Color{ 0.0f, 155.0f, 105.0f } })
	{
		m_Renderer = CreateScoped<Renderer>(m_Window->GetGraphics());
		m_RenderTarget = m_Window->GetGraphics()->GetRenderTarget();
		m_Window->AddListener<WindowResizeEvent>(EventType::WindowResize, std::bind(&GameApplication::OnResize, this, std::placeholders::_1));
		m_Window->AddListener<WindowUpdateEvent>(EventType::WindowUpdate, std::bind(&GameApplication::OnUpdate, this, std::placeholders::_1));
		InitGameState();
	}

	~GameApplication()
	{
		SafeRelease(&m_WhiteBrush);
		SafeRelease(&m_BallBgBrush);
		SafeRelease(&m_AlignedCircleBgBrush);
		SafeRelease(&m_DividerRectBgBrush);
	}

	void Run()
	{
		while (!m_Window->ShouldClose())
		{
			Timestep currentTime;
			m_GameState.DeltaTime = currentTime - m_GameState.LastFrameTime;
			m_GameState.ElapsedTime += m_GameState.DeltaTime;
			m_GameState.LastFrameTime = currentTime;

			Render();
			Sleep(Cast<DWORD>(1000.0f / 120));
		}
	}
private:
	void InitGameState()
	{
		m_RenderTarget->CreateSolidColorBrush(Color{ 255.0f, 255.0f, 255.0f }, &m_WhiteBrush);
		m_RenderTarget->CreateSolidColorBrush(Color{ 155.0f, 200.0f, 155.0f }, &m_AlignedCircleBgBrush);
		m_RenderTarget->CreateSolidColorBrush(Color{ 0.0f, 175.0f, 125.0f, 155.0f }, &m_DividerRectBgBrush);
		m_GameState.FirstPlayerScore = 0;
		m_GameState.SecondPlayerScore = 0;
		m_GameState.PaddleWidth = 10.0f;
		m_GameState.PaddleHeight = 100.0f;

		RECT rc;
		GetClientRect(m_Window->GetWindow(), &rc);
		m_GameState.WindowWidth = Cast<float>(rc.right - rc.left);
		m_GameState.WindowHeight = Cast<float>(rc.bottom - rc.top);
		m_GameState.PaddleDistanceX = m_GameState.WindowWidth - m_GameState.PaddleWidth;
		m_GameState.PaddleDistanceY = m_GameState.WindowHeight - m_GameState.PaddleHeight;

		m_GameState.LeftPaddle = {
			m_GameState.PaddleWidth, m_GameState.PaddleHeight,
			{ 20.0f, m_GameState.PaddleDistanceY / 2 },
			m_WhiteBrush,
			2.5f
		};
		m_GameState.RightPaddle = {
			m_GameState.PaddleWidth, m_GameState.PaddleHeight,
			{ m_GameState.PaddleDistanceX - 20.0f, m_GameState.PaddleDistanceY / 2 },
			m_WhiteBrush,
			2.5f
		};

		m_GameState.BallWidth = 20.0f;
		m_GameState.BallHeight = 20.0f;
		m_GameState.BallDistanceX = (m_GameState.WindowWidth - m_GameState.BallWidth) / 2;
		m_GameState.BallDistanceY = (m_GameState.WindowHeight - m_GameState.BallHeight) / 2;
		m_GameState.BallMovementTimeX = 1.0f;
		m_GameState.BallMovementTimeY = 2.0f;

		m_RenderTarget->CreateSolidColorBrush(Color{ 255.0f, 155.0f, 0.0f }, &m_BallBgBrush);
		m_GameState.Ball = {
			m_GameState.BallWidth, m_GameState.BallHeight,
			{m_GameState.BallDistanceX, m_GameState.BallDistanceY},
			m_BallBgBrush
		};
	}

	bool CheckCollision(const ShapeStyle& circle, const ShapeStyle& rect)
	{
		float distX = std::abs(circle.Position.X - rect.Position.X - rect.Width / 2);
		float distY = std::abs(circle.Position.Y - rect.Position.Y - rect.Height / 2);
		float radius = min(circle.Width, circle.Height) / 2;

		if (distX > (rect.Width / 2 + circle.Width / 2)) return false;
		if (distY > (rect.Height / 2 + radius)) return false;

		if (distX <= (rect.Width / 2)) return true;
		if (distY <= (rect.Height / 2)) return true;

		float dx = distX - rect.Width / 2;
		float dy = distY - rect.Height / 2;
		return (dx * dx + dy * dy <= (radius * radius));
	}

	void DrawPaddles()
	{
		m_Renderer->DrawRectangle(m_GameState.LeftPaddle);
		m_Renderer->DrawRectangle(m_GameState.RightPaddle);
	}

	void DrawBall()
	{

		float velocityX = m_GameState.BallDistanceX / m_GameState.BallMovementTimeX * m_GameState.DeltaTime;
		float velocityY = m_GameState.BallDistanceY / m_GameState.BallMovementTimeY * m_GameState.DeltaTime;
		m_GameState.Ball.Position.X += velocityX;
		m_GameState.Ball.Position.Y += velocityY;
		float radius = m_GameState.Ball.Width / 2;

		if (CheckCollision(m_GameState.Ball, m_GameState.LeftPaddle))
		{
			if (m_GameState.BallMovementTimeX < 0)
			{
				m_GameState.BallMovementTimeX *= -0.97f;
			}
		}
		if (CheckCollision(m_GameState.Ball, m_GameState.RightPaddle))
		{
			if (m_GameState.BallMovementTimeX > 0)
			{
				m_GameState.BallMovementTimeX *= -0.97f;
			}
		}

		if (m_GameState.Ball.Position.Y > m_GameState.WindowHeight - m_GameState.Ball.Height)
		{
			m_GameState.Ball.Position.Y = m_GameState.WindowHeight - m_GameState.Ball.Height;
			m_GameState.BallMovementTimeY *= -1.0f;
		}
		if (m_GameState.Ball.Position.Y < 0)
		{
			m_GameState.Ball.Position.Y = 0;
			m_GameState.BallMovementTimeY *= -1.0f;
		}

		m_Renderer->DrawCircle(m_GameState.Ball);
	}

	void DrawScore()
	{
		if (m_GameState.Ball.Position.X > m_GameState.WindowWidth)
		{
			m_GameState.FirstPlayerScore += 1;
			ResetScore();
		}
		if (m_GameState.Ball.Position.X < 0)
		{
			m_GameState.SecondPlayerScore += 1;
			ResetScore();
		}

		TextStyle firstPlayerScoreStyle = {
			100.0f, 0.0f,
			{(m_GameState.WindowWidth - 50.0f) / 4, 10.0f},
			nullptr, m_WhiteBrush, Font(24.0f, L"Arial", DWRITE_FONT_WEIGHT_DEMI_BOLD)
		};
		m_Renderer->RenderText(std::to_wstring(m_GameState.FirstPlayerScore), firstPlayerScoreStyle);

		TextStyle secondPlayerScoreStyle = {
			100.0f, 0.0f, { m_GameState.WindowWidth * 3.0f / 4, 10.0f },
			nullptr, m_WhiteBrush, Font(24.0f, L"Arial", DWRITE_FONT_WEIGHT_DEMI_BOLD)
		};
		m_Renderer->RenderText(std::to_wstring(m_GameState.SecondPlayerScore), secondPlayerScoreStyle);
	}

	void DrawAppearance()
	{
		ShapeStyle alignedCircle = {
			m_GameState.WindowWidth / 2, m_GameState.WindowHeight / 2,
			{ (m_GameState.WindowWidth - (m_GameState.WindowWidth / 2)) / 2,
			(m_GameState.WindowHeight - (m_GameState.WindowWidth / 2)) / 2 },
			m_AlignedCircleBgBrush
		};
		m_Renderer->DrawCircle(alignedCircle);

		ShapeStyle dividerRect = {
			m_GameState.WindowWidth / 2, m_GameState.WindowHeight,
			{ m_GameState.WindowWidth / 2,
			0.0f },
			m_DividerRectBgBrush
		};
		m_Renderer->DrawRectangle(dividerRect);

		ShapeStyle alignedLine = {
			2.0f, m_GameState.WindowHeight,
			{ (m_GameState.WindowWidth - 2.0f) / 2.0f, 0.0f },
			m_WhiteBrush
		};
		m_Renderer->DrawRectangle(alignedLine);
	}

	void ResetScore()
	{
		PlaySound(L"assets/win-sound-effect.wav", nullptr, SND_ASYNC);
		m_GameState.BallMovementTimeX = 1.0f;
		m_GameState.BallMovementTimeY = 2.0f;
		m_GameState.Ball.Position.X = m_GameState.BallDistanceX;
		m_GameState.Ball.Position.Y = m_GameState.BallDistanceY;
	}

	void HandleKeyPress()
	{
		float movementTime = 1.0f;
		float velocity = m_GameState.PaddleDistanceY / movementTime * m_GameState.DeltaTime;
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			if (m_GameState.RightPaddle.Position.Y > velocity)
			{
				m_GameState.RightPaddle.Position.Y -= velocity;
			}
			else
			{
				m_GameState.RightPaddle.Position.Y = 0.0f;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			if (m_GameState.RightPaddle.Position.Y < m_GameState.PaddleDistanceY)
			{
				m_GameState.RightPaddle.Position.Y += velocity;
			}
			else
			{
				m_GameState.RightPaddle.Position.Y = m_GameState.PaddleDistanceY;
			}
		}
		if (GetAsyncKeyState(L'W') & 0x8000)
		{
			if (m_GameState.LeftPaddle.Position.Y > velocity)
			{
				m_GameState.LeftPaddle.Position.Y -= velocity;
			}
			else
			{
				m_GameState.LeftPaddle.Position.Y = 0.0f;
			}
		}
		if (GetAsyncKeyState(L'S') & 0x8000)
		{
			if (m_GameState.LeftPaddle.Position.Y < m_GameState.PaddleDistanceY)
			{
				m_GameState.LeftPaddle.Position.Y += velocity;
			}
			else
			{
				m_GameState.LeftPaddle.Position.Y = m_GameState.PaddleDistanceY;
			}
		}
	}

	void OnResize(const WindowResizeEvent& e)
	{
		m_GameState.WindowWidth = e.Width;
		m_GameState.WindowHeight = e.Height;
		m_GameState.RightPaddle.Position.X = e.Width - m_GameState.RightPaddle.Width - 20.0f;
		m_GameState.PaddleDistanceX = e.Width - m_GameState.RightPaddle.Width;
		m_GameState.PaddleDistanceY = e.Height - m_GameState.RightPaddle.Height;
		m_GameState.BallDistanceX = (e.Width - m_GameState.Ball.Width) / 2;
		m_GameState.BallDistanceY = (e.Height - m_GameState.Ball.Height) / 2;
	}

	void OnUpdate(const WindowUpdateEvent& e)
	{
		Render();
	}

	void Render()
	{
		m_RenderTarget->BeginDraw();
		m_Renderer->ClearScreen(m_Window->GetStyle().BackgroundColor);

		DrawAppearance();
		DrawPaddles();
		DrawBall();
		DrawScore();
		HandleKeyPress();

		m_RenderTarget->EndDraw();
	}
private:
	Scoped<Renderer> m_Renderer;
	ID2D1HwndRenderTarget* m_RenderTarget = nullptr;
	ID2D1SolidColorBrush* m_WhiteBrush = nullptr;
	ID2D1SolidColorBrush* m_BallBgBrush = nullptr;
	ID2D1SolidColorBrush* m_AlignedCircleBgBrush = nullptr;
	ID2D1SolidColorBrush* m_DividerRectBgBrush = nullptr;
	GameState m_GameState;
};