#pragma once

#include "Transition.h"

namespace D2DLib
{

	class D2DLIB_API InterpolatorTransition : public Transition<float>
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

		void Update() override;
	private:
		bool m_IsFirst = true;
	};

}