#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "AnimatedSprite.h"
#include <iostream>

namespace TheProject
{
	class FieldEvent
	{
	public:
		FieldEvent(sf::FloatRect bounds, void(*content)(), std::string name = "UNNKNOWN");
		~FieldEvent();

		void check(sf::FloatRect other);
		inline void reset()
		{
			std::cout << "FieldEvent '" << m_name << "' resetted." << std::endl;
			m_triggered = false;
		}
		const sf::FloatRect getBounds() const { return m_bounds; }

	private:
		sf::FloatRect m_bounds;
		void(*m_content)();
		bool m_triggered;
		std::string m_name;
	};
}