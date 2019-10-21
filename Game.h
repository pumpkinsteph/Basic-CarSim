#pragma once
#include "Car.h"
#include "Ground.h"

#define WIDTH 1200
#define HEIGHT 600

class Game
{
private:
	Car* car;
	Ground* cliff;
	Ground* ground;
	sf::RenderWindow* window;

	float startX, startY;
	float gravity;

	void gameOver(float deltaTime);
	void restartGame();

public:
	Game(sf::RenderWindow &window);
	~Game();

	void update(float deltaTime);
	void draw();
};