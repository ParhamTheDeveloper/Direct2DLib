#pragma once

#include "Direct2DLib/Direct2DLib.h"

using namespace D2DLib;

class GameApplication : public Application
{
public:
	GameApplication(const String& title, UInt width, UInt height)
		: Application(title, width, height)
	{
	}

	void InitializeResources() override
	{
		CreateLightTransitions();
		CreateLightResources();
	}

	void UninitializeResources() override
	{
		ReleaseLightResources();
		for (auto& block : m_Blocks)
		{
			block.BackgroundColor.Release();
		}
		for (auto& triangle : m_Triangles)
		{
			triangle.BackgroundColor.Release();
		}
	}

	void InitializeEvents() override
	{
		m_Window->AddListener<ApplicationRenderEvent>(EventType::ApplicationRender, BindEventCallback(&GameApplication::OnRender, this));
		m_Window->AddListener<MouseMoveEvent>(EventType::MouseMove, BindEventCallback(&GameApplication::OnMouseMove, this));
		m_Window->AddListener<MouseClickEvent>(EventType::MouseClick, BindEventCallback(&GameApplication::OnClick, this));
		m_Window->AddListener<KeyPressEvent>(EventType::KeyPress, BindEventCallback(&GameApplication::OnKeyPress, this));
	}

	void OnRender(const ApplicationRenderEvent& e)
	{
		const Style clientSize = m_Window->GetClientSize();
		const Vector2 distance(clientSize.Width, clientSize.Height);

		const float movementTime = 2.0f;
		static const Vector2 movementSpeed = distance / movementTime;

		static Vector2 direction;

		if (Input::Keyboard::IsKeyPressedAsync(L'W'))
		{
			direction.Y = -1;
			direction.X = 0;
		}
		if (Input::Keyboard::IsKeyPressedAsync(L'S'))
		{
			direction.Y = 1;
			direction.X = 0;
		}
		if (Input::Keyboard::IsKeyPressedAsync(L'A'))
		{
			direction.X = -1;
			direction.Y = 0;
		}
		if (Input::Keyboard::IsKeyPressedAsync(L'D'))
		{
			direction.X = 1;
			direction.Y = 0;
		}

		m_Camera.Position += direction * movementSpeed * e.DeltaTime;
		m_Camera.Update();
		direction = 0.0f;
	}

	void OnMouseMove(const MouseMoveEvent& e)
	{
		Vector2 lightCenter = e.Position - Vector2(m_Light.Radius.X, m_Light.Radius.Y);
		m_Light.Position = lightCenter;
	}

	void OnClick(const MouseClickEvent& e)
	{
		if (e.IsRight)
		{
			auto msg = L"Turned {} the light"fmt;
			m_IsLightOn = !m_IsLightOn;
			if (m_IsLightOn)
			{
				Debug::Info(msg + L"On");
			}
			else
			{
				Debug::Info(msg + L"Off");
			}
			CreateLightTransitions();
		}
		else
		{
			auto msg = L"Added a new shape with the type of [{}] And position of [{}, {}]"fmt;
			switch (m_ShapeType)
			{
				case ShapeStyleType::Rectangle:
					{
						RectangleStyle blockStyle(50.0f, 50.0f, 0.0f, CreateBrush(Color(60.0f, 45.0f, 50.0f)));
						Vector2 blockCenter = e.Position - Vector2(blockStyle.Width / 2.0f, blockStyle.Height / 2.0f);
						blockStyle.Position = blockCenter;
						m_Blocks.push_back(blockStyle);
						Debug::Info(msg.$(L"Rectangle", blockStyle.Position.X, blockStyle.Position.Y));
					}
					break;

				case ShapeStyleType::Triangle:
					{
						TriangleStyle triangleStyle(50.0f, 50.0f, 0.0f, CreateBrush(Color(60.0f, 45.0f, 50.0f)));
						Vector2 triangleCenter = e.Position - Vector2(triangleStyle.Width / 2.0f, triangleStyle.Height / 2.0f);
						triangleStyle.VertexA = triangleCenter + Vector2(-triangleStyle.Width / 2.0f, triangleStyle.Height / 2.0f);
						triangleStyle.VertexB = triangleCenter + Vector2(0.0f, -triangleStyle.Height / 2.0f);
						triangleStyle.VertexC = triangleCenter + Vector2(triangleStyle.Width / 2.0f, triangleStyle.Height / 2.0f);
						m_Triangles.push_back(triangleStyle);
						Debug::Info(msg.$(L"Triangle", triangleCenter.X, triangleCenter.Y));
					}
					break;
			}
		}
	}

	void OnKeyPress(const KeyPressEvent& e)
	{
		auto msg = L"Changed the Shape type to [{}]"fmt;
		switch (e.Character)
		{
			case L'r':
				{
					if (m_ShapeType != ShapeStyleType::Rectangle)
					{
						m_ShapeType = ShapeStyleType::Rectangle;
						Debug::Success(msg + L"Rectangle");
					}
				}
				break;

			case L't':
				{
					if (m_ShapeType != ShapeStyleType::Triangle)
					{
						m_ShapeType = ShapeStyleType::Triangle;
						Debug::Success(msg + L"Triangle");
					}
				}
				break;
		}
	}

	void CreateLightTransitions()
	{
		if (m_IsLightOn)
		{
			m_LightTransition.SetStartValue(0.0f);
			m_LightTransition.SetEndValue(255.0f);
			m_LightTransition.Reset();
		}
		else
		{
			m_LightTransition.SetStartValue(255.0f);
			m_LightTransition.SetEndValue(0.0f);
			m_LightTransition.Reset();
		}
		m_TransitionManager.AddTransition(m_LightTransition);
	}

	void DrawShapes()
	{
		for (auto& block : m_Blocks)
		{
			DrawRectangle(block);
		}
		for (auto& triangle : m_Triangles)
		{
			DrawTriangle(triangle);
		}
	}

	void CreateLightResources()
	{
		m_Light.Radius = 150.0f;
		Color firstColor = Color(255.0f, 255.0f, 255.0f, m_LightTransition.GetValue());
		Brush backgroundBrush = CreateRadialGradientBrush(
			m_Light,
			Vector<GradientStop>({
				GradientStop(0.0f, firstColor),
				GradientStop(1.0f, Color(255.0f, 255.0f, 255.0f, 0.0f))
			})
		);
		m_Light.BackgroundColor = backgroundBrush;
	}

	void DrawLight()
	{
		DrawCircle(m_Light);

		ShapeStyle shadowStyle;
		shadowStyle.BackgroundColor = CreateBrush(Color(20.0f, 20.0f, 20.0f, m_LightTransition.GetValue()));
		Light light(m_Light, shadowStyle, true);
		light.Update(m_Light.Position);
		
		light.Look(m_Blocks);
		light.Look(m_Triangles);

		DrawShapes();
		shadowStyle.BackgroundColor.Release();
	}

	void ReleaseLightResources()
	{
		m_Light.BackgroundColor.Release();
	}

	void Render(DeltaTime deltaTime)
	{
		CreateLightResources();

		DrawLight();

		m_TransitionManager.UpdateTransitions();
		ReleaseLightResources();
	}
private:
	CircleStyle m_Light;
	Vector<RectangleStyle> m_Blocks;
	Vector<TriangleStyle> m_Triangles;
	bool m_IsLightOn = true;
	InterpolatorTransition m_LightTransition = { 0.0f, 255.0f, 0.2f };
	TransitionManager m_TransitionManager;
	ShapeStyleType m_ShapeType = ShapeStyleType::Default;
	Camera m_Camera;
};