#include "Car.h"

Car::Car(float width, float height) {
	this->speed = 100;
	this->weight = 100;

	this->width = width;
	this->height = height;

	body.setSize(sf::Vector2f(width, height));
	body.setFillColor(sf::Color::White);
}

Car::~Car() {

}

void Car::movementInput(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x += speed * deltaTime;
	}

	move(movement);
}

void Car::move(sf::Vector2f& movement) {
	body.move(movement);
}

void Car::changePos(float x, float y) {
	body.setPosition(x, y);
}

float Car::getWidth() {
	return this->width;
}

float Car::getHeight() {
	return this->height;
}

void Car::update(float deltaTime) {
	movementInput(deltaTime);
}

void Car::draw(sf::RenderWindow* window) {
	window->draw(body);
}
