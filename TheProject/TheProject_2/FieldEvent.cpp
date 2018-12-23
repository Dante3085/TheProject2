#include "FieldEvent.h"

namespace TheProject
{
	FieldEvent::FieldEvent(sf::FloatRect bounds, void(*content)(), std::string name)
		: m_bounds{ bounds }, m_content{ content }, m_triggered{ false }, m_name{ name }
	{
	}

	FieldEvent::~FieldEvent()
	{
	}

	void FieldEvent::check(sf::FloatRect other)
	{
		if (!m_triggered && m_bounds.intersects(other))
		{
			m_content();
			m_triggered = true;
			std::cout << "FieldEvent '" << m_name << "' triggered." << std::endl;
		}
	}
}