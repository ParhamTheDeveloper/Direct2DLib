#include "Direct2DLibpch.h"
#include "DeltaTime.h"

namespace D2DLib
{

	bool g_IsFirstInitialization = true;
	LARGE_INTEGER g_Frequency;

	DeltaTime::DeltaTime()
		: m_Time(0.0f), m_IsFirstCall(true), m_LastFrameTime()
	{
		if (g_IsFirstInitialization)
		{
			QueryPerformanceFrequency(&g_Frequency);
			g_IsFirstInitialization = false;
		}
	}

	void DeltaTime::Tick()
	{
		if (m_IsFirstCall)
		{
			QueryPerformanceCounter(&m_LastFrameTime);
			m_IsFirstCall = false;
		}
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		m_Time = static_cast<float>(currentTime.QuadPart - m_LastFrameTime.QuadPart) / static_cast<float>(g_Frequency.QuadPart);
		m_LastFrameTime = currentTime;
	}

	void DeltaTime::Reset()
	{
		QueryPerformanceCounter(&m_LastFrameTime);
		m_Time = 0.0f;
	}

}