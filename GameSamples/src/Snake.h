#pragma once

#include "Direct2DLib/Direct2DLib.h"

using namespace D2DLib;

inline constexpr const UInt g_Cols = 20;

inline const Vector2 GetBoardPosition()
{
	UInt size = g_Cols * g_Cols;
	float windowWidth = GetMainWindow()->GetClientSize().Width;
	float windowHeight = GetMainWindow()->GetClientSize().Height;
	return {
		(windowWidth - size) / 2.0f,
		(windowHeight - size) / 2.0f
	};
}

class Board
{
public:
	Board()
	{
		Size = g_Cols * g_Cols;
		m_RowsBrush = CreateBrush({ 20.0f, 155.0f, 50.0f });
		m_ColsBrush = CreateBrush({ 20.0f, 135.0f, 55.0f });
	}

	~Board()
	{
		SafeRelease(&m_RowsBrush);
		SafeRelease(&m_ColsBrush);
	}

	void Draw()
	{
		DrawBoard();
		const Vector2 boardPos = GetBoardPosition();
		for (UInt i = 0; i < g_Cols; i++)
		{
			for (UInt j = 0; j < g_Cols; j++)
			{
				float x = Cast<float>(g_Cols * i);
				float y = Cast<float>(g_Cols * j);
				Vector2 blockPos = { x + ceil(boardPos.X), y + ceil(boardPos.Y) };
				auto blockBrush = (i + j) % 2 ? m_RowsBrush : m_ColsBrush;
				ShapeStyle blockStyle = {
					g_Cols, g_Cols, blockPos, blockBrush
				};
				DrawRectangle(blockStyle);
			}
		}
	}
private:
	void DrawBoard()
	{
		const Vector2 boardPos = GetBoardPosition();
		auto boardOutlineBrush = CreateBrush({ 255.0f, 255.0f, 255.0f });
		ShapeStyle boardOutlineStyle = {
			Size, Size, boardPos, nullptr, 0.0f, { 2.0f, boardOutlineBrush }
		};
		DrawRectangle(boardOutlineStyle);
		SafeRelease(&boardOutlineBrush);
	}
public:
	float Size;
private:
	Resource<ID2D1SolidColorBrush> m_RowsBrush;
	Resource<ID2D1SolidColorBrush> m_ColsBrush;
};

class Food
{
public:
	Food(const Deque<Vector2>& snake)
		: m_Snake(snake)
	{
		UpdatePosition();
	}

	void Draw()
	{
		RectangleStyle appleStyle = {
			g_Cols, g_Cols, GetPosition()
		};
		Texture apple(L"assets/apple.jpg", appleStyle);
		RenderTexture(apple);
	}

	void UpdatePosition()
	{
		float x = Cast<float>(GetRandomNumber(1, g_Cols - 1));
		float y = Cast<float>(GetRandomNumber(1, g_Cols - 1));
		m_Position = GeneratePosition();
		while ((std::find(m_Snake.begin(), m_Snake.end(), m_Position) != m_Snake.end()))
		{
			m_Position = GeneratePosition();
		}
	}

	const Vector2 GetPosition() const { return m_Position * Vector2{ g_Cols, g_Cols } + GetBoardPosition(); }
private:
	const Vector2 GeneratePosition()
	{
		float x = Cast<float>(GetRandomNumber(1, g_Cols - 1));
		float y = Cast<float>(GetRandomNumber(1, g_Cols - 1));
		return { x, y };
	}
private:
	Vector2 m_Position;
	Deque<Vector2> m_Snake;
};

class Snake
{
public:
	Snake()
	{
		ResetPosition();
	}

	void Draw()
	{
		for (UInt i = 0; i < Body.size(); i++)
		{
			float x = Cast<float>(Body[i].X);
			float y = Cast<float>(Body[i].Y);
			const Vector2 snakePos = { x * g_Cols, y * g_Cols };
			auto snakeBrush = CreateBrush({ Body.size() * 2.5f, Body.size() * 5.0f, Body.size() * 10.0f });
			ShapeStyle snakeBodyStyle = {
				g_Cols, g_Cols, snakePos + GetBoardPosition(), snakeBrush, 4.0f
			};
			DrawRectangle(snakeBodyStyle);
			SafeRelease(&snakeBrush);
		}
	}

	void MoveSnakePosition(bool& allowMove)
	{
		Vector2 head = Body[0];
		if (Input::Keyboard::IsKeyPressedAsync(L'W') && m_Direction.Y != 1.0f && allowMove)
		{
			m_Direction = { 0.0f, -1.0f };
			allowMove = false;
		}
		if (Input::Keyboard::IsKeyPressedAsync(L'S') && m_Direction.Y != -1.0f && allowMove)
		{
			m_Direction = { 0.0f, 1.0f };
			allowMove = false;
		}
		if (Input::Keyboard::IsKeyPressedAsync(L'A') && m_Direction.X != 1.0f && allowMove)
		{
			m_Direction = { -1.0f, 0.0f };
			allowMove = false;
		}
		if (Input::Keyboard::IsKeyPressedAsync(L'D') && m_Direction.X != -1.0f && allowMove)
		{
			m_Direction = { 1.0f, 0.0f };
			allowMove = false;
		}
	}

	void CollidesFood()
	{
		m_CanAddBodyPart = true;
	}

	void UpdateBody()
	{
		Body.push_front(Body[0] + m_Direction);
		if (m_CanAddBodyPart)
		{
			m_CanAddBodyPart = false;
		}
		else
		{
			Body.pop_back();
		}
	}

	void ResetPosition()
	{
		Body = { { 7.0f, 10.0f }, { 8.0f, 10.0f }, { 9.0f, 10.0f } };
		m_Direction = { 1.0f, 0.0f };
	}

	const Vector2 GetPosition() const { return Body[0] * Vector2{ g_Cols, g_Cols } + GetBoardPosition(); }
public:
	Deque<Vector2> Body;
private:
	Vector2 m_Direction;
	bool m_CanAddBodyPart = false;
};

class GameApplication : public Application
{
public:
	GameApplication(const String& title, UInt width, UInt height)
		: Application(title, width, height, { Color{ 0.0f, 155.0f, 155.0f } })
	{
		m_Board = CreateScoped<Board>();
		m_Snake = CreateScoped<Snake>();
		m_Food = CreateScoped<Food>(m_Snake->Body);
		InitTransitions();
	}
private:
	void Render(DeltaTime deltaTime)
	{
		m_Board->Draw();
		m_Food->Draw();
		m_Snake->Draw();
		m_Snake->MoveSnakePosition(m_AllowMove);
		DrawScore();

		if (m_IsRunning)
		{
			if (EventTriggered(0.2f))
			{
				m_AllowMove = true;
				m_Snake->UpdateBody();
				SnakeCollidesFood();
				SnakeCollidesBoardEdges();
			}
		}
		else
		{
			ShowGameOverDialog();
		}
	}

	bool EventTriggered(float interval)
	{
		Timestep currentTime;
		if (currentTime - m_LastFrameTime >= interval)
		{
			m_LastFrameTime = currentTime;
			return true;
		}
		return false;
	}

	void SnakeCollidesFood()
	{
		if (m_Snake->GetPosition() == m_Food->GetPosition())
		{
			PlaySound(L"assets/snake-eating-food.wav", nullptr, SND_ASYNC);
			m_Food->UpdatePosition();
			m_Snake->CollidesFood();
			m_Score += 1;
		}
	}

	void SnakeCollidesBoardEdges()
	{
		if (m_Snake->Body[0].X > g_Cols - 1 || m_Snake->Body[0].X == -1 ||
			m_Snake->Body[0].Y > g_Cols - 1 || m_Snake->Body[0].Y == -1)
		{
			PlaySound(L"assets/snake-hissing.wav", nullptr, SND_ASYNC);
			GameOver();
		}
	}

	void DrawScore()
	{
		Style windowSize = m_Window->GetClientSize();
		auto textBrush = CreateBrush({ 255.0f, 255.0f, 255.0f });
		TextStyle textStyle = {
			300.0f, 0.0f,
			{ GetBoardPosition().X, (GetBoardPosition().Y - 40.0f) },
			nullptr, textBrush, Font(20.0f, L"Bahnschrift")
		};
		RenderText(L"Score: " + std::to_wstring(m_Score), textStyle);
	}

	void ShowGameOverDialog()
	{
		Style windowSize = m_Window->GetClientSize();
		m_DialogBackgroundTransition->Update();
		auto rectBrush = CreateBrush(Color{ 0.0f, 0.0f, 0.0f, m_DialogBackgroundTransition->GetValue() });
		ShapeStyle rectStyle = {
			windowSize.Width, windowSize.Height, { 0.0f, 0.0f }, rectBrush
		};
		DrawRectangle(rectStyle);
		SafeRelease(&rectBrush);

		m_DialogTextTransition->Update();
		auto textBrush = CreateBrush({
			m_DialogTextTransition->GetValue(),
			m_DialogTextTransition->GetValue(), 
			m_DialogTextTransition->GetValue(),
			m_DialogTextTransition->GetValue()
		});
		TextStyle textStyle = {
			300.0f, 0.0f,
			{
				(windowSize.Width - 300.0f) / 2.0f,
				(windowSize.Height - 32.0f * 3.0f) / 2.0f,
			},
			nullptr, textBrush, Font(32.0f, L"Bahnschrift")
		};
		RenderText(L"Game Over!\nPress space to play again.", textStyle);
		SafeRelease(&textBrush);

		if (Input::Input::Keyboard::IsKeyPressed(VK_SPACE))
		{
			InitTransitions();
			m_IsRunning = true;
		}
	}

	void InitTransitions()
	{
		m_DialogBackgroundTransition = CreateScoped<InterpolatorTransition>(0.0f, 220.0f, 0.5f, TransitionTiming::Linear);
		m_DialogTextTransition = CreateScoped<InterpolatorTransition>(0.0f, 255.0f, 0.5f, TransitionTiming::Linear);
	}

	void GameOver()
	{
		m_IsRunning = false;
		m_Score = 0;
		m_Snake->ResetPosition();
		m_Food->UpdatePosition();
	}
private:
	Scoped<Board> m_Board;
	Scoped<Snake> m_Snake;
	Scoped<Food> m_Food;
	Timestep m_LastFrameTime;
	bool m_IsRunning = true;
	Scoped<InterpolatorTransition> m_DialogBackgroundTransition;
	Scoped<InterpolatorTransition> m_DialogTextTransition;
	UInt m_Score;
	bool m_AllowMove = false;
};