#include "Game.h"

Game::Game(sf::RenderWindow &window) {
	this->car = new Car("car.png",15.0f, 8.0f, 1393.0f);
	this->ground = new Ground("ground.png",WIDTH, 20.0f);
	this->cliff = new Ground("cliff.png",WIDTH*0.5, HEIGHT*0.5);

	this->startX = 0.0f;
	this->startY = HEIGHT*0.5f - this->car->getHeight();
	this->gravity = 9.82f;

	this->car->changePos(startX, startY);
	this->cliff->changePos(0.0f, HEIGHT*0.5f);
	this->ground->changePos(0.0f, HEIGHT - this->ground->getHeight());

	this->window = &window;
}

Game::~Game() {
	delete this->car;
	delete this->ground;
	delete this->cliff;
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