#pragma once
#include "Car.h"
#include "Ground.h"

#define WIDTH 1200
#define HEIGHT 600

class Game
{
private:
	// Classes
	Car* car;
	Ground* cliff;
	Ground* ground;
	sf::RenderWindow* window;

	// Variables
	float startX, startY;
	float gravity;

	// Private functions
	void gameOver(float deltaTime);
	void restetGame();

public:
	// Constructors and Destructors
	Game(sf::RenderWindow &window);
	~Game();

	// Functions
	void update(float deltaTime);
	void draw();
};