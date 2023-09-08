#pragma once

#include "Base.h"

namespace D2DLib
{

	class D2DLIB_API DeltaTime
	{
	public:
		DeltaTime();

		void Tick();
		void Reset();

		const float& Get() const { return m_Time; };
		operator const float& () const { return m_Time; };
	private:
		LARGE_INTEGER m_LastFrameTime;
		float m_Time;
		bool m_IsFirstCall;
	};

}