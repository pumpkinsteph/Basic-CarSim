#include "Ground.h"

Ground::Ground(string fileName, float width, float height) {

	this->texture.loadFromFile(fileName);
	this->body.setTexture(this->texture);

	this->width = width;
	this->height = height;
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
