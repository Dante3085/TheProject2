#include "FieldEvent.h"

namespace TheProject
{
	FieldEvent::FieldEvent(sf::FloatRect bounds, void(*content)())
		: m_bounds{ bounds }, m_content{ content }, m_triggered{ false }
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
		}
	}
}