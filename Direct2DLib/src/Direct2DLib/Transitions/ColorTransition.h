#pragma once

#include "Transition.h"

namespace D2DLib
{

	class D2DLIB_API ColorTransition : public Transition<Color>
	{
	public:
		ColorTransition(
			Color start,
			Color end,
			float duration,
			bool autoStart = false,
			TransitionTiming timing = TransitionTiming::EaseInOut
		);
		ColorTransition(
			Color start,
			Color end,
			float duration,
			TransitionTiming timing
		);

		void Update() override;
	private:
		bool m_IsFirst = true;
	};

}