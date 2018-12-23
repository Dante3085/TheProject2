#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

#include "AnimatedSprite.h"
#include "FieldEvent.h"
#include "Event.h"

using namespace TheProject;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "TheProject2");

	std::cout << window.getSize().x << ", " << window.getSize().y << std::endl;

	float xSpeed, ySpeed;
	xSpeed = window.getSize().x * 0.0001f;
	ySpeed = window.getSize().y * 0.0001f;

	std::cout << "xSpeed: " << xSpeed << ", ySpeed: " << ySpeed << std::endl;

	AnimatedSprite sprite {{"demon-idle.png"}, {0, 0} };
	sprite.addAnimation(IDLE, 0, 160, 144, 0, 0, 6, 0.2f);
	sprite.setAnimation(IDLE);

	// FieldEvent fieldEvent{ sf::FloatRect{ 500, 500, 300, 300 },  &saySomething};
	Event myEvent{ sf::FloatRect{ 100, 0, 100, 100 }, [&sprite]()
	{
		return sprite.getPosition().x >= 100 && sprite.getPosition().x <= 200;
	}, [&sprite]()
	{
		std::cout << "Sprite ist in x [100, 200] !" << std::endl;
		sprite.setPosition(500, 500);
	}}; 

	sf::RectangleShape recShape{ { myEvent.getBounds().width, myEvent.getBounds().height } };
	recShape.setFillColor(sf::Color::Blue);
	recShape.setPosition(myEvent.getBounds().left, myEvent.getBounds().top);

	sf::RectangleShape spriteBox{ { sprite.getBounds().width, sprite.getBounds().height } };
	spriteBox.setFillColor(sf::Color::Transparent);
	spriteBox.setOutlineColor(sf::Color::Red);
	spriteBox.setOutlineThickness(2.f);
	spriteBox.setPosition(sprite.getBounds().left, sprite.getBounds().top);

	// NACHVOLLZIEHEN
	// timepoint for delta time measurement
	auto timepoint = std::chrono::steady_clock::now();

	while (window.isOpen())
	{
		// Das ist eine Änderung
		// Noch ne Änderung

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
					myEvent.reset();
			}

			// we don't process other types of events
			default:
				break;
			}
		}

		// AnimatedSprite smooth bewegen (Beachte: https://www.sfml-dev.org/tutorials/2.5/window-events.php; https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			sprite.move(-xSpeed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			sprite.move(xSpeed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			sprite.move(0, -ySpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			sprite.move(0, ySpeed);
	

		// NACHVOLLZIEHEN
		// get dt
		float deltaTime;
		{
			const auto new_tp = std::chrono::steady_clock::now();

			// duration
			deltaTime = std::chrono::duration<float>(new_tp - timepoint).count();
			timepoint = new_tp;
		}

		spriteBox.setPosition(sprite.getBounds().left, sprite.getBounds().top);

		myEvent.check();

		window.clear();
		sprite.update(deltaTime);
		window.draw(recShape);
		window.draw(sprite);
		window.draw(spriteBox);
		window.display();

	}

	return 0;
}