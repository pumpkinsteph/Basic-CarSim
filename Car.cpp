#include "Car.h"

Car::Car(float width, float height, float weight) {
	this->speed = 100;

	this->weight = weight;
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

float Car::gravityForce(float deltaTime, float gravity, float slopeAngle) {
	return this->weight*gravity*cos(slopeAngle)*deltaTime;
}

float Car::gravityRolling(float deltaTime, float gravity, float slopeAngle) {
	return this->weight*gravity*sin(slopeAngle)*deltaTime;
}

void Car::update(float deltaTime, float cliffWidth, float groundHeight, float gravity) {
	movementInput(deltaTime);
	sf::Vector2f currentPos = this->body.getPosition();
	sf::Vector2f movement(0.0f, 0.0f);

	if (currentPos.x > cliffWidth && currentPos.y < groundHeight) {
		movement.y += gravity * deltaTime;
		this->move(movement);
	}
	/*
	if car.x > cliffWidth
		apply gravity on movement
	if car.y > groundHeight - carHeight
		stop gravity on movement
	*/
}

void Car::draw(sf::RenderWindow* window) {
	window->draw(body);
}
