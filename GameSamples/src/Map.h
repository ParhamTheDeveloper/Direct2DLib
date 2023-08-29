#pragma once

#include "Direct2DLib/Direct2DLib.h"

using namespace D2DLib;

class GameApplication : public Application
{
public:
	GameApplication(const String& title, UInt width, UInt height)
		: Application(title, width, height)
	{
		SetVSync(true);
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
			block.Outline.Color.Release();
		}
		for (auto& triangle : m_Triangles)
		{
			triangle.BackgroundColor.Release();
			triangle.Outline.Color.Release();
		}
	}

	void InitializeEvents() override
	{
		m_Window->AddListener<MouseMoveEvent>(EventType::MouseMove, BindEventCallback(&GameApplication::OnMouseMove, this));
		m_Window->AddListener<MouseClickEvent>(EventType::MouseClick, BindEventCallback(&GameApplication::OnClick, this));
		m_Window->AddListener<KeyPressEvent>(EventType::KeyPress, BindEventCallback(&GameApplication::OnKeyPress, this));
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
			m_IsLightOn = !m_IsLightOn;
			CreateLightTransitions();
		}
		else
		{
			String msg = L"Added a new shape with the type of [{}] And position of [{}, {}]";
			switch (m_ShapeType)
			{
				case ShapeStyleType::Rectangle:
					{
						RectangleStyle blockStyle(25.0f, 25.0f, 0.0f, CreateBrush(Color(60.0f, 45.0f, 50.0f)));
						blockStyle.Outline = Outline(2.0f, CreateBrush(Color(30.0f, 155.0f, 225.0f)));
						Vector2 blockCenter = e.Position - Vector2(blockStyle.Width / 2.0f, blockStyle.Height / 2.0f);
						blockStyle.Position = blockCenter;
						m_Blocks.push_back(blockStyle);
						Debug::Info(std::vformat(msg, std::make_wformat_args(
							L"Rectangle", blockStyle.Position.X, blockStyle.Position.Y)));
					}
					break;

				case ShapeStyleType::Triangle:
					{
						TriangleStyle triangleStyle(25.0f, 25.0f, 0.0f, CreateBrush(Color(60.0f, 45.0f, 50.0f)));
						triangleStyle.Outline = Outline(2.0f, CreateBrush(Color(30.0f, 155.0f, 225.0f)));
						Vector2 triangleCenter = e.Position - Vector2(triangleStyle.Width / 2.0f, triangleStyle.Height / 2.0f);
						triangleStyle.VertexA = triangleCenter + Vector2(-triangleStyle.Width / 2.0f, triangleStyle.Height / 2.0f);
						triangleStyle.VertexB = triangleCenter + Vector2(0.0f, -triangleStyle.Height / 2.0f);
						triangleStyle.VertexC = triangleCenter + Vector2(triangleStyle.Width / 2.0f, triangleStyle.Height / 2.0f);
						m_Triangles.push_back(triangleStyle);
						Debug::Info(std::vformat(msg, std::make_wformat_args(
							L"Triangle", triangleCenter.X, triangleCenter.Y)));
					}
					break;
			}
		}
	}

	void OnKeyPress(const KeyPressEvent& e)
	{
		const String msg = L"Changed the Shape type to {}";
		switch (e.Character)
		{
			case L'r':
				{
					m_ShapeType = ShapeStyleType::Rectangle;
					Debug::Info(std::vformat(msg, std::make_wformat_args(L"Rectangle")));
				}
				break;

			case L't':
				{
					m_ShapeType = ShapeStyleType::Triangle;
					Debug::Info(std::vformat(msg, std::make_wformat_args(L"Triangle")));
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
		auto backgroundBrush = CreateRadialGradientBrush(
			m_Light,
			Vector<GradientStop>({
				GradientStop(0.0f, Color(255.0f, 255.0f, 255.0f, m_LightTransition.GetValue())),
				GradientStop(1.0f, Color(255.0f, 255.0f, 255.0f, 0.0f))
			})
		);
		m_Light.BackgroundColor = backgroundBrush;
	}

	void DrawLight()
	{
		DrawCircle(m_Light);

		ShapeStyle shadowStyle;
		shadowStyle.BackgroundColor = CreateBrush(Color(20.0f, 20.0f, 20.0f));
		Light light(m_Light, shadowStyle, true);
		light.Update(m_Light.Position);
		
		if (m_IsLightOn)
		{
			light.Look(m_Blocks);
			light.Look(m_Triangles);
		}

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
};