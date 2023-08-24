#include "pch.h"
#include "Transition.h"

namespace D2DLib
{

	Transition::Transition(float duration, float autoUpdate, TransitionTiming timing)
		: m_Duration(duration), m_ElapsedTime(0.0f), m_IsDone(false), m_AutoUpdate(autoUpdate), m_Timing(timing)
	{
		SetTimer();
		m_IsFirst = true;
	}

	void Transition::Stop(bool condition)
	{
		if (condition)
		{
			m_IsDone = true;
			if (m_AutoUpdate)
			{
				GetMainWindow()->DestroyTimer(m_TimerId);
			}
		}
	}

	void Transition::SetTimer()
	{
		srand(Cast<UInt>(time(nullptr)));
		m_TimerId = Cast<UInt>(rand());
		if (m_AutoUpdate)
		{
			GetMainWindow()->CreateTimer(true, m_TimerId, GetScreenRefreshRate(), [this](const WindowTimerEvent& e)
				{
					Update();
				});
		}
	}

	void Transition::ResetFrameTime()
	{
		if (m_IsFirst)
		{
			m_LastFrameTime = Timestep();
			m_IsFirst = false;
		}
	}

	float Transition::SetProgress(float progress)
	{
		switch (m_Timing)
		{
			case TransitionTiming::Linear:
				{
					return progress;
				}

			case TransitionTiming::Ease:
				{
					return Ease(progress);
				}

			case TransitionTiming::EaseIn:
				{
					return EaseIn(progress);
				}

			case TransitionTiming::EaseInOut:
				{
					return EaseInOut(progress);
				}
		}
		return progress;
	}

}