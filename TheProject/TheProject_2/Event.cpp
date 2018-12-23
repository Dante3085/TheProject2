#include "Event.h"

namespace TheProject
{
	Event::Event(sf::FloatRect bounds, std::function<bool()> trigger, std::function<void()> behaviour, std::string name)
		: m_bounds{ bounds }, m_trigger{ trigger }, m_behaviour{ behaviour }, m_triggered{ false }, m_name{ name }
	{
	}

	void Event::check()
	{
		if (!m_triggered && m_trigger())
		{
			m_behaviour();
			m_triggered = true;
		}
	}
}
