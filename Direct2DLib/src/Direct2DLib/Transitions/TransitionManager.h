#pragma once

#include "InterpolatorTransition.h"
#include "ColorTransition.h"

namespace D2DLib
{

	class D2DLIB_API TransitionManager
	{
	public:
		TransitionManager(bool canRemoveWhenDone = false);
		~TransitionManager();

		void AddTransition(InterpolatorTransition& transition);
		void AddTransition(ColorTransition& transition);
		void UpdateTransitions();
		
		template<typename TransitionType>
		const Vector<TransitionType> GetTransitionByType()
		{
			Vector<TransitionType> foundTransitions;
			foundTransitions = GetByType<TransitionType>(m_InterpolatorTransitions);
			foundTransitions = GetByType<TransitionType>(m_ColorTransitions);
			return foundTransitions;
		}
	private:
		template<typename TransitionType, typename Type>
		const Vector<TransitionType> GetByType(const Vector<Type>& transitions)
		{
			Vector<TransitionType> foundTransitions;
			for (const auto& i : transitions)
			{
				if (typeid(*i) == typeid(TransitionType))
				{
					foundTransitions.push_back(i);
				}
			}
			return foundTransitions;
		}

		template<typename Type>
		void UpdateByType(Vector<Type>& transitions)
		{
			for (auto& transition : transitions)
			{
				if (transition->IsDone())
				{
					auto it = std::find(transitions.begin(), transitions.end(), transition);
					transitions.erase(it);
				}
				transition->Update();
			}
		}
	private:
		Vector<InterpolatorTransition*> m_InterpolatorTransitions;
		Vector<ColorTransition*> m_ColorTransitions;
		bool m_CanRemoveWhenDone;
	};

}