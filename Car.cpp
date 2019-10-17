#include "Car.h"

Car::Car(string fileName, float width, float height, float weight) {

	this->texture.loadFromFile(fileName);
	this->body.setTexture(this->texture);

	this->speedX = 50.0f;
	this->speedY = 0.0f;

	this->weight = weight;
	this->width = width;
	this->height = height;
}

Car::~Car() {

}

void Car::movementInput(float deltaTime) {
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement.x += this->speedX * deltaTime;
	}
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

/*//the force that pushes the car down
float Car::gravityForce(float deltaTime, float gravity, float slopeAngle) {
	return this->weight*gravity*cos(slopeAngle)*deltaTime;
}
*/

////the force that makes the car roll backwards or forwards on a ramp
float Car::gravityRolling(float deltaTime, float gravity, float slopeAngle) {
	return this->weight*gravity*sin(slopeAngle)*deltaTime;
}

void Car::update(float deltaTime, float cliffWidth, float groundHeight, float gravity) {
	movementInput(deltaTime);
	sf::Vector2f currentPos = this->body.getPosition();

	if (currentPos.x > cliffWidth && currentPos.y < groundHeight) {
		this->speedY += gravity * deltaTime;
		body.move(0.0f, this->speedY * deltaTime);
	}

	/*
	if on a slope
		apply gravity Rolling
	*/
}

void Car::draw(sf::RenderWindow* window) {
	window->draw(body);
}
