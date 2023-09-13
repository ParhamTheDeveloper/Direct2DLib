#include "Direct2DLib/Direct2DLib.h"

// It's recommended to use the namespace but you can still continue without using it.
using namespace D2DLib;

class GameApplication : public Application
{
public:
	GameApplication(const String& title, UInt width, UInt height)
		: Application(title, width, height), m_IsLightOn(true)
	{
		// You can use vsync to limit your frame rate to your monitor refresh rate.
		// It's always recommended to use vsync so you won't have any screen tearing, otherwise use LimitFrameRate method.
		SetFrameRate(60);
		m_Window->SetIcon(L"assets/icons/application-icon.ico");
	}

	// This method is used to initialize the events of the window and the application.
	void InitializeEvents() override
	{
		m_Window->AddListener<MouseMoveEvent>(EventType::MouseMove, BindEventCallback(&GameApplication::OnMouseMove, this));
		m_Window->AddListener<MouseDownEvent>(EventType::MouseDown, BindEventCallback(&GameApplication::OnMouseDown, this));
	}

	void InitializeResources() override
	{
		m_LightSourceAlphaColor = CreateScoped<InterpolatorTransition>(0.0f, 255.0f, 0.5f);
		m_TransitionManager.AddTransition(*m_LightSourceAlphaColor);
	}

	void UninitializeResources() override
	{
		for (auto& rect : m_RectBlocks)
		{
			rect.BackgroundColor.Release();
		}
	}

	void OnMouseMove(const MouseMoveEvent& e)
	{
		// We want the mouse cursor to be in the center of our light source so we subtract the mouse position from the light's radius.
		m_LightSourceStyle.Position = e.Position - m_LightSourceStyle.Radius;
	}

	void OnMouseDown(const MouseDownEvent& e)
	{
		if (e.IsRight)
		{
			m_IsLightOn = !m_IsLightOn;
			if (m_IsLightOn)
			{
				m_LightSourceAlphaColor->SetStartValue(0.0f);
				m_LightSourceAlphaColor->SetEndValue(255.0f);
				m_LightSourceAlphaColor->Reset();
			}
			else
			{
				m_LightSourceAlphaColor->SetStartValue(255.0f);
				m_LightSourceAlphaColor->SetEndValue(0.0f);
				m_LightSourceAlphaColor->Reset();
			}
		}
		else
		{
			RectangleStyle rectStyle(50.0f, 50.0f);
			const Vector2 blockCenter(e.Position.X - rectStyle.Width / 2, e.Position.Y - rectStyle.Height / 2);
			rectStyle.Position = blockCenter;
			rectStyle.BackgroundColor = CreateBrush(Color(60.0f, 25.0f, 40.0f));
			m_RectBlocks.push_back(rectStyle);
		}
	}

	// Since the in order to move the linear gradient brush we need to recreate it again (change it's position)
	// we create a seprate method to handle the initialization of our light source style.
	void CreateLightResources()
	{
		Color firstColor(55.0f, 205.0f, 255.0f, m_LightSourceAlphaColor->GetValue()), secondColor = firstColor;
		secondColor.a = 0.0f;

		m_LightSourceStyle.Radius = 200.0f;
		m_LightSourceStyle.BackgroundColor = CreateRadialGradientBrush(
			m_LightSourceStyle,
			{ GradientStop(0.0f, firstColor), GradientStop(1.0f, secondColor) }
		);
	}

	// This method automaticly gets called in each frame.
	// It's used for creating the resources that are going to be released after every frame (e.g. a ShapeStyle)
	void InitializeFrameResources() override
	{
		CreateLightResources();
		m_ShadowStyle.BackgroundColor = CreateBrush(Color(30.0f, 30.0f, 70.0f, m_LightSourceAlphaColor->GetValue()));
		m_ShadowStyle2.BackgroundColor = CreateBrush(Color(30.0f, 30.0f, 30.0f, 150.0f));
	}

	// Releases the initialized resources in InitializeFrameResources in each frame.
	void UninitializeFrameResources() override
	{
		m_LightSourceStyle.BackgroundColor.Release();
		m_ShadowStyle.BackgroundColor.Release();
		m_ShadowStyle2.BackgroundColor.Release();
	}

	// The actual Render method which is obviously used to render stuff to the screen.
	void Render(DeltaTime deltaTime) override
	{
		const Style clientStyle = m_Window->GetClientSize();
		const Vector2 screenCenter = (Vector2(clientStyle.Width, clientStyle.Height) / 2.0f) - m_LightSourceStyle.Radius;
		
		DrawCircle(m_LightSourceStyle);

		Light light(m_LightSourceStyle, m_ShadowStyle, true);
		light.Update(m_LightSourceStyle.Position);
		light.Look(m_RectBlocks);

		Light light2(m_LightSourceStyle, m_ShadowStyle2, true);
		light2.Update(screenCenter);
		light2.Look(m_RectBlocks);

		for (const auto& rect : m_RectBlocks)
		{
			DrawRectangle(rect);
		}

		m_TransitionManager.UpdateTransitions();
	}
private:
	// Note that you can use a ShapeStyle or a RectangleStyle too but it's recommended to use CircleStyle for more flexibility.
	CircleStyle m_LightSourceStyle;
	ShapeStyle m_ShadowStyle, m_ShadowStyle2;
	// This variable is used to store wheter the light is open or not.
	bool m_IsLightOn;
	// It's recommended to use Scoped for the classes that don't have a default constructor.
	// Initialize Scoped member variables inside the InitializeResources method.
	Scoped<InterpolatorTransition> m_LightSourceAlphaColor;
	// Use transition manager when you have more than one or two transitions in your app.
	TransitionManager m_TransitionManager;
	Vector<RectangleStyle> m_RectBlocks;
};
