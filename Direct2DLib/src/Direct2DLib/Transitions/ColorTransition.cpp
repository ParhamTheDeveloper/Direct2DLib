#include "pch.h"

#include "ColorTransition.h"

namespace D2DLib
{

	ColorTransition::ColorTransition(
		Color start,
		Color end,
		float duration,
		bool autoStart,
		TransitionTiming timing
	)
		: Transition(duration, autoStart, timing), m_Start(start), m_End(end), m_Value(start)
	{
	}

	ColorTransition::ColorTransition(Color start, Color end, float duration, TransitionTiming timing)
		: Transition(duration, false, timing), m_Start(start), m_End(end), m_Value(start)
	{
	}


	void ColorTransition::Update()
	{
		ResetFrameTime();
		if (!m_IsDone)
		{
			Timestep currentTime;
			float deltaTime = currentTime - m_LastFrameTime;
			m_ElapsedTime += deltaTime;
			m_LastFrameTime = currentTime;

			float progress = m_ElapsedTime / m_Duration;
			progress = SetProgress(progress);

			m_Value.r = Lerp(m_Start.r, m_End.r, progress);
			m_Value.g = Lerp(m_Start.g, m_End.g, progress);
			m_Value.b = Lerp(m_Start.b, m_End.b, progress);
			m_Value.a = Lerp(m_Start.a, m_End.a, progress);
			Stop(progress >= 1);
		}
	}

}