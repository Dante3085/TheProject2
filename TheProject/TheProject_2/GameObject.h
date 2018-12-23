#pragma once
#include <vector>
#include "Event.h"

namespace TheProject
{
	class GameObject
	{
	public:
		GameObject(/*std::vector<Event> events = std::vector<Event>{}*/);
		virtual ~GameObject(){}

		virtual void update(float deltaTime) = 0;
		/*void checkEvents();
		void addEvent(Event& e)
		{
			m_events.push_back(e);
		}
		void resetEvents()
		{
			for (Event& e : m_events)
				e.reset();
		}*/

	private:
		//std::vector<Event> m_events;
	};
}