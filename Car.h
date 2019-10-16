#pragma once
#include <SFML\Graphics.hpp>

class Car {
private:
	sf::RectangleShape body;
	sf::Texture texture;

	float speed;		//
	float weight;		//kg

	float width;
	float height;

	void movementInput(float deltaTime);
	void move(sf::Vector2f& movement);
public:
	Car(float width, float height, float weight);
	~Car();

	float getWidth();
	float getHeight();
	void changePos(float x, float y);

	float gravityForce(float deltaTime, float gravity, float slopeAngle);
	float gravityRolling(float deltaTime, float gravity, float slopeAngle);
	void update(float deltaTime, float cliffWidth, float groundHeight, float gravity);
	void draw(sf::RenderWindow* window);
};

//Comments for Steph later
/*
	//what variables does the car need saved and what will be sent in from Game?
	//when you create a car you have to create it with a set of variables that determinate car type
	//or we can maybe save variables for different car types somewhere that later can be picked from? but that might be better in game

	//we have the speed of the car, the speed will determinate how many pixels the car should move between frames

	//FgN = mass*gravity*cos(slopeAngle);	//the force that pushes the car down
	//FgP = mass*gravity*sin(slopeAngle);	//the force that makes the car roll backwards or forwards on a ramp
	//FNf = //front tire force that pushes up the tire. Only exist if tire is on ground
	//FNr = //rear tire force that pushes up the tire Only exist if tire is on ground
	//Fn = FNf + FNr = mass*gravity*cos(slopeAngle);
	//if collision with the ground, nullify the force

	//FT = Tw/rw //the force that makes the tires spin and therefore makes the car go forward
	//Tw = torque applied to the wheels
	//rw = wheen radious

	//Te = //something wheel turning

	//FD = 1/2CDpv^2A	//dynamic dragforce that recents the cars forward motion
	//p = air density
	//A = frontal Area
	//the square of the velovity magnitue v
	//drag coefficient CD

	//FRf = //front wheel something
	//FRr = //rear wheel something
	//Private functions
*/
