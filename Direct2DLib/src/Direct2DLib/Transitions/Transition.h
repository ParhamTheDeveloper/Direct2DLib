#pragma once

#include "Direct2DLib/Core/Window.h"
#include "Direct2DLib/Core/DeltaTime.h"

namespace D2DLib
{

	enum class D2DLIB_API TransitionTiming
	{
		Linear,
		Ease,
		EaseIn,
		EaseOut,
		EaseInOut
	};

	template<typename ValueType>
	class D2DLIB_API Transition
	{
	public:
		Transition(
			const ValueType& startValue,
			const ValueType& endValue,
			float duration,
			bool autoUpdate,
			TransitionTiming timing
		) :
			m_Start(startValue),
			m_End(endValue),
			m_Value(startValue),
			m_Duration(duration),
			m_ElapsedTime(0.0f),
			m_IsDone(false),
			m_AutoUpdate(autoUpdate),
			m_Timing(timing)
		{
			SetTimer();
			m_IsFirst = true;
		}

		void SetStartValue(const ValueType& startValue)
		{
			m_Start = startValue;
		}

		void SetEndValue(const ValueType& endValue)
		{
			m_End = endValue;
		}

		void SetDuration(float duration)
		{
			m_Duration = duration;
		}

		const ValueType& GetValue() const { return m_Value; };
		const ValueType& GetStartValue() const { return m_Start; }
		const ValueType& GetEndValue() const { return m_End; }
		float GetDuration() const { return m_Duration; }
		bool IsDone() const { return m_IsDone; }

		virtual void Stop(bool condition = true)
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

		virtual void Reset()
		{
			m_IsDone = false;
			m_Value = m_Start;
			m_ElapsedTime = 0.0f;
			m_DeltaTime.Reset();
			if (m_AutoUpdate)
			{
				SetTimer();
			}
		}

		virtual void Update() = 0;
	private:
		void SetTimer()
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
	protected:
		float SetProgress(float progress)
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
	protected:
		float m_Duration;
		DeltaTime m_DeltaTime;
		UInt m_TimerId;
		float m_ElapsedTime;
		bool m_IsDone, m_AutoUpdate;
		TransitionTiming m_Timing;
		bool m_IsFirst;
		ValueType m_Value, m_Start, m_End;
	};

}