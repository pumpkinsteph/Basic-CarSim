#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "Drivetrain.h"
#include "DragForce.h"

using namespace std;

class Car {
private:
	//car
	sf::Texture texture;
	sf::Sprite body;

	//meters
	sf::RectangleShape rpmMeter;
	sf::RectangleShape throttleMeter;

	sf::Font font;
	sf::Text speedometer;
	sf::Text rpmText;
	sf::Text distanceText;

	//forces
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f force;

	Drivetrain engine;

	//variables
	float mass;
	float dragArea;
	float Cdx, Cdy;
	float frictionForce;
	float distanceTravel;

	//car size
	float carDepth;
	float carWidth;
	float carHeight;

	//sprite size
	float spriteWidth;
	float spriteHeight;

	void updateUI();

public:
	Car(string fileName, float carWidth, float carHeight, float spriteWidth, float spriteHeight, float weight);
	~Car();

	float getCarWidth();
	float getCarHeight();
	float getSpriteWidth();
	float getSpriteHeight();

	void reset(float x, float y);
	void changePos(float x, float y);
	void update(float deltaTime, float cliffWidth, float groundHeight, float gravity);
	void draw(sf::RenderWindow* window);
};
