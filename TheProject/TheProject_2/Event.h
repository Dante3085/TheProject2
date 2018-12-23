#pragma once
#include <functional>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <string>

namespace TheProject
{
	class Event
	{
	public:
		Event(sf::FloatRect bounds, std::function<bool()> trigger, std::function<void()> behaviour, std::string name = "UNDEFINED");
		~Event(){}

		void check();
		const sf::FloatRect getBounds() const { return m_bounds; }
		void reset()
		{
			std::cout << "FieldEvent '" << m_name << "' resetted." << std::endl;
			m_triggered = false;
		}

	private:
		sf::FloatRect m_bounds;
		std::function<bool()> m_trigger;
		std::function<void()> m_behaviour;
		bool m_triggered;
		std::string m_name;
	};
}
