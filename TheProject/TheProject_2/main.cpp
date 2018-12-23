#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include "AnimatedSprite.h"
#include "FieldEvent.h"

using namespace TheProject;

AnimatedSprite* sprite;

void saySomething()
{
	sprite->move(50, 0);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "TheProject2");

	sprite = new AnimatedSprite{{"demon-idle.png"}, {0, 0} };
	sprite->addAnimation(IDLE, 0, 160, 144, 0, 0, 6, 0.2f);
	sprite->setAnimation(IDLE);

	FieldEvent fieldEvent{ sf::FloatRect{ 500, 500, 300, 300 },  &saySomething};

	sf::RectangleShape recShape{ { fieldEvent.getBounds().width, fieldEvent.getBounds().height } };
	recShape.setFillColor(sf::Color::Blue);
	recShape.setPosition(fieldEvent.getBounds().left, fieldEvent.getBounds().top);

	// NACHVOLLZIEHEN
	// timepoint for delta time measurement
	auto timepoint = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		// Das ist eine Änderung

		sf::Event event;

		// while there are pending events...
		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();

				if (event.key.code == sf::Keyboard::R)
					fieldEvent.reset();
			}

			// we don't process other types of events
			default:
				break;
			}
		}

		// AnimatedSprite smooth bewegen (Beachte: https://www.sfml-dev.org/tutorials/2.5/window-events.php; https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			sprite->move(-.5f, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			sprite->move(.5f, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			sprite->move(0, -.5f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			sprite->move(0, .5f);
	

		// NACHVOLLZIEHEN
		// get dt
		float deltaTime;
		{
			const auto new_tp = std::chrono::steady_clock::now();

			// duration
			deltaTime = std::chrono::duration<float>(new_tp - timepoint).count();
			timepoint = new_tp;
		}

		fieldEvent.check(sprite->getBounds());

		window.clear();
		sprite->update(deltaTime);
		window.draw(recShape);
		window.draw(*sprite);
		window.display();
	}

	return 0;
}