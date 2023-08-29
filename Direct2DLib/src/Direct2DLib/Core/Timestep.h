#pragma once

#include "Base.h"

namespace D2DLib
{

	class D2DLIB_API Timestep
	{
	public:
		Timestep()
		{
			LARGE_INTEGER frequency, time;
			QueryPerformanceFrequency(&frequency);
			QueryPerformanceCounter(&time);
			m_Time = static_cast<float>(time.QuadPart) / static_cast<float>(frequency.QuadPart);
		}

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }

		Timestep& operator=(const Timestep& other)
		{
			m_Time = other.m_Time;
			return *this;
		}

		operator float() const { return m_Time; }

	private:
		float m_Time;
	};

}