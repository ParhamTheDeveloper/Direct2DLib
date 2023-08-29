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
		: Transition(start, end, duration, autoStart, timing)
	{
	}

	ColorTransition::ColorTransition(Color start, Color end, float duration, TransitionTiming timing)
		: Transition(start, end, duration, false, timing)
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