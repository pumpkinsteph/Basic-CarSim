#include "Ground.h"

Ground::Ground(float width, float height) {
	this->width = width;
	this->height = height;
	this->body.setSize(sf::Vector2f(width, height));
	body.setFillColor(sf::Color::Red);
}

Ground::~Ground() {

}

void Ground::changePos(float x, float y) {
	body.setPosition(x, y);

}

float Ground::getWidth() {
	return this->width;
}

float Ground::getHeight() {
	return this->height;
}

void Ground::update(float deltaTime) {

}

void Ground::draw(sf::RenderWindow* window) {
	window->draw(body);
}
