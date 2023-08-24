#pragma once

#include "Transition.h"

namespace D2DLib
{

	class InterpolatorTransition : public Transition
	{
	public:
		InterpolatorTransition(
			float start,
			float end,
			float duration,
			bool autoStart = false,
			TransitionTiming timing = TransitionTiming::EaseInOut
		);
		InterpolatorTransition(float start, float end, float duration, TransitionTiming timing);

		float GetValue() const { return m_Value; };
		float GetStartValue() const { return m_Start; }
		float GetEndValue() const { return m_End; }

		void Update() override;
	private:
		float m_Start, m_End, m_Value;
		bool m_IsFirst = true;
	};

}