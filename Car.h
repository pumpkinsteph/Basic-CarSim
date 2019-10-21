#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Drivetrain.h"

using namespace std;

class Car {
private:
	sf::Texture texture;
	sf::Sprite body;

	sf::RectangleShape rpmMeter;
	sf::RectangleShape throttleMeter;
	sf::RectangleShape throttleBack;

	sf::Font font;
	sf::Text speedometer;
	sf::Text rpmText;

	Drivetrain engine;

	float speedX;
	float speedY;
	float mass;
	float width;
	float height;
	float frictionForce;
	float acceleration;
	float forceX;
public:
	Car(string fileName, float width, float height, float weight);
	~Car();

	float getWidth();
	float getHeight();
	void changePos(float x, float y);

	//float gravityForce(float deltaTime, float gravity, float slopeAngle);
	float gravityRolling(float deltaTime, float gravity, float slopeAngle);
	void reset(float x, float y);
	void update(float deltaTime, float cliffWidth, float groundHeight, float gravity);
	void draw(sf::RenderWindow* window);
};
