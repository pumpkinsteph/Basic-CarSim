#include "Game.h"

Game::Game(sf::RenderWindow &window) 
	:car("car.png", 4.3f, 1.2f, 15.0f, 8.0f, 1393.0f), ground("ground.png", WIDTH, 20.0f), cliff("cliff.png", WIDTH * 0.5, HEIGHT * 0.5) {
	this->startX = 0.0f;
	this->startY = HEIGHT - this->cliff.getHeight() - this->car.getSpriteHeight();
	this->gravity = 9.82f;

	this->car.changePos(startX, startY);
	this->cliff.changePos(0.0f, HEIGHT - this->cliff.getHeight());
	this->ground.changePos(0.0f, HEIGHT - this->ground.getHeight());

	this->window = &window;
}

Game::~Game() {

}



void Game::update(float deltaTime) {
	this->car.update(deltaTime, this->cliff.getWidth(), HEIGHT - this->ground.getHeight() - this->car.getSpriteHeight(), this->gravity);

	//restart game if R is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		this->restartGame();
	}
}

void Game::draw() {
	this->ground.draw(this->window);
	this->cliff.draw(this->window);
	this->car.draw(this->window);
}

void Game::restartGame() {
	this->car.reset(this->startX, this->startY);
}