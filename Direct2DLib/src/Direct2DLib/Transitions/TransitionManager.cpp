#include "pch.h"
#include "TransitionManager.h"

namespace D2DLib
{

	TransitionManager::TransitionManager(bool canRemoveWhenDone)
		: m_Transitions(), m_CanRemoveWhenDone(canRemoveWhenDone)
	{
	}

	TransitionManager::TransitionManager(const Vector<Transition*>& transitions)
	{
		m_Transitions = transitions;
	}

	TransitionManager::~TransitionManager()
	{
		m_Transitions.clear();
	}

	void TransitionManager::AddTransition(Transition* transition)
	{
		if (transition)
		{
			auto it = std::find(m_Transitions.begin(), m_Transitions.end(), transition);
			if (it == m_Transitions.end())
			{
				m_Transitions.push_back(transition);
			}
		}
	}

	void TransitionManager::UpdateTransitions()
	{
		for (const auto& transition : m_Transitions)
		{
			if (transition->IsDone())
			{
				if (m_CanRemoveWhenDone)
				{
					auto it = std::find(m_Transitions.begin(), m_Transitions.end(), transition);
					m_Transitions.erase(it);
				}
				continue;
			}
			transition->Update();
		}
	}

}