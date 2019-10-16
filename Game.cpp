#include "Game.h"

// Constructors and Destructors
Game::Game(sf::RenderWindow &window) {
	this->car = new Car(15.0f, 8.0f, 1500.0f);
	this->ground = new Ground(WIDTH, 200.0f);
	this->cliff = new Ground(WIDTH*0.5, HEIGHT*0.5);

	this->startX = 0.0f;
	this->startY = HEIGHT*0.5 - this->car->getHeight();
	this->gravity = 9.12f;

	this->car->changePos(startX, startY);
	this->cliff->changePos(0.0f, HEIGHT*0.5);
	this->ground->changePos(0.0f, HEIGHT - this->ground->getHeight());

	this->window = &window;
}

Game::~Game() {
	delete this->car;
	delete this->cliff;
	delete this->ground;
}

void Game::update(float deltaTime) {
	car->update(deltaTime, this->cliff->getWidth(), HEIGHT - this->ground->getHeight() - this->car->getHeight(), this->gravity);
}

void Game::draw() {
	ground->draw(window);
	cliff->draw(window);
	car->draw(window);
}

void Game::gameOver(float deltaTime) {

}

void Game::restetGame() {

}