#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "AnimatedSprite.h"
namespace TheProject
{
	class FieldEvent
	{
	public:
		FieldEvent(sf::FloatRect bounds, void(*content)());
		~FieldEvent();

		void check(sf::FloatRect other);
		inline void reset()
		{
			m_triggered = false;
		}
		const sf::FloatRect getBounds() const { return m_bounds; }

	private:
		sf::FloatRect m_bounds;
		void(*m_content)();
		bool m_triggered;
	};
}