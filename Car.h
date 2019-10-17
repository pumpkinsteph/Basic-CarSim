#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class Car {
private:
	sf::Texture texture;
	sf::Sprite body;

	float speedX;
	float speedY;
	float weight;

	float width;
	float height;

	void movementInput(float deltaTime);
public:
	Car(string fileName, float width, float height, float weight);
	~Car();

	float getWidth();
	float getHeight();
	void changePos(float x, float y);

	//float gravityForce(float deltaTime, float gravity, float slopeAngle);
	float gravityRolling(float deltaTime, float gravity, float slopeAngle);
	void update(float deltaTime, float cliffWidth, float groundHeight, float gravity);
	void draw(sf::RenderWindow* window);
};
