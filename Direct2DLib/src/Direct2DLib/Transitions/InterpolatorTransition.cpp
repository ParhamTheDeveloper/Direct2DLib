#include "Direct2DLibpch.h"
#include "InterpolatorTransition.h"

namespace D2DLib
{

	InterpolatorTransition::InterpolatorTransition(
		float start,
		float end,
		float duration,
		bool autoStart,
		TransitionTiming timing
	)
		: Transition(start, end, duration, autoStart, timing)
	{
	}

	InterpolatorTransition::InterpolatorTransition(float start, float end, float duration, TransitionTiming timing)
		: Transition(start, end, duration, false, timing)
	{
	}

	void InterpolatorTransition::Update()
	{
		if (!m_IsDone)
		{
			m_DeltaTime.Tick();
			m_ElapsedTime += m_DeltaTime;

			float progress = m_ElapsedTime / m_Duration;
			progress = SetProgress(progress);
			
			m_Value = Lerp(m_Start, m_End, progress);
			Stop(progress >= 1);
		}
	}

}