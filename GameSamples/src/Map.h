#pragma once

#include "Direct2DLib/Direct2DLib.h"

using namespace D2DLib;

class GameApplication : public Application
{
public:
    GameApplication(const String& title, UInt width, UInt height)
        : Application(title, width, height, ApplicationWindowInfo(Color(), true))
    {
        InitializeEvents();
    }

    void InitializeResources() override
    {
        m_LightStyle = { 800.0f, 800.0f, { 0.0f, 0.0f } };
        CreateLightBrush();
        GenerateWall();
    };

    void UninitializeResources() override
    {
        SafeRelease(&m_LightStyle.BackgroundColor);
        for (ShapeStyle& rect : m_Rectangles)
        {
            SafeRelease(&rect.BackgroundColor);
        }
    }

    void InitializeEvents() override
    {
        m_Window->AddListener<MouseMoveEvent>(EventType::MouseMove,
            BindEventCallback(&GameApplication::OnMouseMove, this));
        m_Window->AddListener<MouseDownEvent>(EventType::MouseDown,
            BindEventCallback(&GameApplication::OnMouseDown, this));
        m_Window->RemoveListener(EventType::WindowResize);
        m_Window->AddListener<KeyDownEvent>(EventType::KeyDown,
            BindEventCallback(&GameApplication::OnKeyDown, this));
    }

    void OnMouseMove(const MouseMoveEvent& e)
    {
        m_MousePos = e.Position;
        if (m_IsLightFollowing)
        {
            m_LightStyle.Position.X = e.Position.X - m_LightStyle.Width / 2.0f;
            m_LightStyle.Position.Y = e.Position.Y - m_LightStyle.Height / 2.0f;
        }
        CreateLightBrush();
    }

    void OnMouseDown(const MouseDownEvent& e)
    {
        auto rectsBrush = CreateBrush({ 30.0f, 30.0f, 30.0f });
        ShapeStyle rect = { 50.0f, 50.0f };
        rect.Position.X = e.Position.X - rect.Width / 2.0f;
        rect.Position.Y = e.Position.Y - rect.Height / 2.0f;
        rect.BackgroundColor = rectsBrush;
        m_Rectangles.push_back(rect);
    }

    void CreateLightBrush()
    {
        m_LightStyle.BackgroundColor = CreateBrush(
            m_LightStyle,
            {
                { 0.0f, Color(255.0f, 255.0f, 255.0f) },
                { 1.0f, Color(255.0f, 255.0f, 255.0f, 0.0f) }
            },
            {}, true
        );
    }

    void OnKeyDown(const KeyDownEvent& e)
    {
        float cameraMovementSpeed = 300.0f;
        if (e.Character == L'O')
        {
            m_IsLightOn = true;
        }
        else if (e.Character == L'C')
        {
            m_IsLightOn = false;
        }
        else if (e.Character == L'U')
        {
            m_IsLightFollowing = false;
        }
        else if (e.Character == L'F')
        {
            m_IsLightFollowing = true;
        }
        if (e.Character == L'W')
        {
            m_Camera.Position.Y -= cameraMovementSpeed * m_Time.DeltaTime;
            m_Camera.Update();
        }
        if (e.Character == L'S')
        {
            m_Camera.Position.Y += cameraMovementSpeed * m_Time.DeltaTime;
            m_Camera.Update();
        }
        if (e.Character == L'A')
        {
            m_Camera.Position.X -= cameraMovementSpeed * m_Time.DeltaTime;
            m_Camera.Update();
        }
        if (e.Character == L'D')
        {
            m_Camera.Position.X += cameraMovementSpeed * m_Time.DeltaTime;
            m_Camera.Update();
        }
    }

    void GenerateWall()
    {
        Style clientSize = m_Window->GetClientSize();
        for (int i = 0; i < 5; i++)
        {
            Vector2 start(Cast<float>(GetRandomNumber(100, Cast<UInt>(clientSize.Width))),
                Cast<float>(GetRandomNumber(100, Cast<UInt>(clientSize.Width))));
            Vector2 end(Cast<float>(GetRandomNumber(100, Cast<UInt>(clientSize.Height))),
                Cast<float>(GetRandomNumber(100, Cast<UInt>(clientSize.Height))));
            m_Walls.push_back(Boundary(start, end));
        }
    }

    void Render(DeltaTime deltaTime) override
    {
        if (m_IsLightOn)
        {
            DrawCircle(m_LightStyle);
        }

        for (const ShapeStyle& rect : m_Rectangles)
        {
            DrawRectangle(rect);
        }

        ShapeStyle shadowStyle;
        shadowStyle.BackgroundColor = CreateBrush(Color(20.0f, 20.0f, 20.0f));
        Light particle(0.0f, shadowStyle, m_LightStyle.Width / 2.0f);
        for (Boundary& wall : m_Walls)
        {
            wall.Draw();
        }
        particle.Update(Vector2(
            m_LightStyle.Position.X + m_LightStyle.Width / 2.0f,
            m_LightStyle.Position.Y + m_LightStyle.Height / 2.0)
        );
        particle.Look(m_Walls);
        SafeRelease(&shadowStyle.BackgroundColor);
    }
private:
    ShapeStyle m_LightStyle;
    Vector<ShapeStyle> m_Rectangles;
    bool m_IsLightOn = false;
    bool m_IsLightFollowing = true;
    Vector2 m_MousePos;
    Camera m_Camera;
    Vector<Boundary> m_Walls;
};