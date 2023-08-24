#pragma once

#include "Event.h"

namespace D2DLib
{
	
	/// <summary>
	/// Subclass of the Window class to handle both system and application Events
	/// </summary>
	class EventListener
	{
	private:
		template<typename EventType>
		using EventCallback = Function<void(const EventType&)>;
	public:
		/// <summary>
		///	Add an event listener to the event listeners map vector
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="eventName"></param>
		/// <param name="listener"></param>
		template<typename T>
		void AddListener(EventType eventName, const EventCallback<T>& listener)
		{
			if (m_Listeners.find(eventName) == m_Listeners.end())
			{
				m_Listeners[eventName] = Vector<EventCallback<Event>>();
			}
			m_Listeners[eventName].push_back([listener, eventName](const Event& event)
			{
				// If the eventName which is a EventType was the same as the event's type
				// we're gonna prepare the event listener for later.
				if (eventName == event.GetType())
				{
					listener(static_cast<const T&>(event));
				}
			});
		}

		/// <summary>
		/// Removes an event listener from the event listeners,
		/// Or it just simply erases the event listeners map
		/// </summary>
		/// <param name="eventName"></param>
		void RemoveListener(EventType eventName)
		{
			auto it = m_Listeners.find(eventName);
			if (it != m_Listeners.end())
			{
				m_Listeners.erase(it);
			}
		}
		
		template<typename T>
		void DispatchEvent(const T& event)
		{
			std::string eventType = typeid(T).name();
			if (m_Listeners.find(eventType) != m_Listeners.end())
			{
				auto& listeners = m_Listeners[eventType];
				for (auto listener : listeners)
				{
					listener(event);
				}
			}
		}

		void DispatchEvent(EventType eventName, const Event& event)
		{
			if (m_Listeners.find(eventName) != m_Listeners.end())
			{
				auto& eventListeners = m_Listeners[eventName];
				for (auto listener : eventListeners)
				{
					// dispatch the event to the event listener
					listener(event);
				}
			}
		}
	protected:
		Map<EventType, Vector<EventCallback<Event>>> m_Listeners;
	};

}
