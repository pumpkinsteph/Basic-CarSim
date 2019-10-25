#include <iostream>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML project");

	float deltaTime = 0.0f;																
	sf::Clock clock;
	Game game(window);
	window.setVerticalSyncEnabled(true);
	
	while (window.isOpen()) {
		deltaTime = clock.restart().asSeconds();
		
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed)
				window.close();
		}
		
		game.update(deltaTime);
		window.clear();
		game.draw();
		window.display();
	}
}