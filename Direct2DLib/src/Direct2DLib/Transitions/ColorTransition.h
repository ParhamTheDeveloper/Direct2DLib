#pragma once

#include "Transition.h"

namespace D2DLib
{

	class ColorTransition : public Transition
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

		const Color& GetColor() const { return m_Value; };
		const Color& GetStartColor() const { return m_Start; }
		const Color& GetEndColor() const { return m_End; }

		void Update() override;
	private:
		Color m_Start, m_End, m_Value;
		bool m_IsFirst = true;
	};

}