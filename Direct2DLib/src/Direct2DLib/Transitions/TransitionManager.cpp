#include "pch.h"
#include "TransitionManager.h"

namespace D2DLib
{

	TransitionManager::TransitionManager(bool canRemoveWhenDone)
		: m_InterpolatorTransitions(), m_ColorTransitions(), m_CanRemoveWhenDone(canRemoveWhenDone)
	{
	}

	TransitionManager::~TransitionManager()
	{
		m_InterpolatorTransitions.clear();
		m_ColorTransitions.clear();
	}

	void TransitionManager::AddTransition(InterpolatorTransition& transition)
	{
		m_InterpolatorTransitions.push_back(&transition);
	}

	void TransitionManager::AddTransition(ColorTransition& transition)
	{
		m_ColorTransitions.push_back(&transition);
	}

	void TransitionManager::UpdateTransitions()
	{
		UpdateByType(m_InterpolatorTransitions);
		UpdateByType(m_ColorTransitions);
	}

}