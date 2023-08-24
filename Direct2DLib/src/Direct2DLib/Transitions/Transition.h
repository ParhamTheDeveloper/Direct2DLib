#pragma once

#include "Direct2DLib/Core/Window.h"

namespace D2DLib
{

	enum class TransitionTiming
	{
		Linear,
		Ease,
		EaseIn,
		EaseOut,
		EaseInOut
	};

	class Transition
	{
	public:
		Transition(float duration, float autoUpdate, TransitionTiming timing);

		float GetDuration() const { return m_Duration; }
		bool IsDone() const { return m_IsDone; }
		
		virtual void Update() = 0;
		virtual void Stop(bool condition = true);
	private:
		void SetTimer();
	protected:
		void ResetFrameTime();
		float SetProgress(float progress);
	protected:
		float m_Duration;
		Timestep m_LastFrameTime;
		UInt m_TimerId;
		float m_ElapsedTime;
		bool m_IsDone, m_AutoUpdate;
		TransitionTiming m_Timing;
		bool m_IsFirst;
	};

}