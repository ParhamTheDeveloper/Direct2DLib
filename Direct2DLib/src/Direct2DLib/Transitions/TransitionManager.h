#pragma once

#include "Transition.h"

namespace D2DLib
{

	class TransitionManager
	{
	public:
		TransitionManager(bool canRemoveWhenDone = false);
		TransitionManager(const Vector<Transition*>& transitions);
		~TransitionManager();

		void AddTransition(Transition* transition);
		void UpdateTransitions();
		
		template<typename TransitionType>
		const Vector<TransitionType> GetTransitionByType()
		{
			Vector<TransitionType> foundTransitions;
			for (const auto& i : m_Transitions)
			{
				if (typeid(*i) == typeid(TransitionType))
				{
					foundTransitions.push_back(*static_cast<TransitionType*>(i));
				}
			}
			return foundTransitions;
		}
	private:
		Vector<Transition*> m_Transitions;
		bool m_CanRemoveWhenDone;
	};

}