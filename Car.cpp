#include "Car.h"

void Car::updateUI() {
	int rpmColour = (int)((float)engine.getRPM() * (255.0f / 7500.0f));
	this->rpmMeter.setFillColor(sf::Color(rpmColour, 255 - rpmColour, 0));
	this->rpmMeter.setSize(sf::Vector2f(this->engine.getRPM() * 500.0f / 7500.0f, 30.0f));

	this->throttleMeter.setSize(sf::Vector2f(this->engine.getThrottle() * 100.0f, 20.0f));

	std::string speed = "Speed:   " + std::to_string((int)(this->velocity.x * 3.6f)) + " km/h";
	this->speedometer.setString(speed);
	std::string revs = "Gear: " + std::to_string(this->engine.getGear()) + "       RPM: " + std::to_string(this->engine.getRPM());
	this->rpmText.setString(revs);

	//this->engine.printValues(this->velocity.x);
}

Car::Car(string fileName, float carWidth, float carHeight, float spriteWidth, float spriteHeight, float weight) {
	this->texture.loadFromFile(fileName);
	this->body.setTexture(this->texture);

	this->velocity = sf::Vector2f(0.0f, 0.0f);
	this->acceleration = sf::Vector2f(0.0f, 0.0f);
	this->force = sf::Vector2f(0.0f, 0.0f);
	this->frictionForce = 0.0f;
	this->dragArea = 2.17f;
	this->Cdx = 0.35f;
	this->Cdy = 1.28f;
	this->mass = weight;
	this->carWidth = carWidth;
	this->carHeight = carHeight;
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->carDepth = 1.8f;
	this->distanceTravel = 0.0f;

	this->rpmMeter.setPosition(400.0f, 25.0f);
	this->rpmMeter.setSize(sf::Vector2f(100.0f, 30.0f));
	this->rpmMeter.setFillColor(sf::Color::Black);

	this->throttleMeter.setPosition(50.0f, 25.0f);
	this->throttleMeter.setSize(sf::Vector2f(20.0f, 5.0f));
	this->throttleMeter.setFillColor(sf::Color::White);

	this->font.loadFromFile("sansation.ttf");
	this->speedometer.setString("SPEED...");
	this->speedometer.setFont(font);
	this->speedometer.setPosition(50.0f, 60.0f);
	this->speedometer.setCharacterSize(24);
	this->speedometer.setColor(sf::Color::White);

	this->rpmText.setString("REVS...");
	this->rpmText.setFont(font);
	this->rpmText.setPosition(500.0f, 60.0f);
	this->rpmText.setCharacterSize(24);
	this->rpmText.setColor(sf::Color::White);

	this->distanceText.setString("");
	this->distanceText.setFont(font);
	this->distanceText.setPosition(500, 250);
	this->distanceText.setCharacterSize(36);
	this->distanceText.setColor(sf::Color::White);
}

Car::~Car() {

}

float Car::getCarWidth() {
	return this->carWidth;
}

float Car::getCarHeight() {
	return this->carHeight;
}

float Car::getSpriteWidth()
{
	return this->spriteWidth;
}

float Car::getSpriteHeight()
{
	return this->spriteHeight;
}

void Car::reset(float x, float y) {
	this->body.setPosition(x, y);
	this->velocity = sf::Vector2f(0.0f, 0.0f);
	this->acceleration = sf::Vector2f(0.0f, 0.0f);
	this->force = sf::Vector2f(0.0f, 0.0f);
	this->frictionForce = 0.0f;
	this->distanceTravel = 0.0f;
	this->distanceText.setString("");
	this->engine.setGear(1);
}

void Car::changePos(float x, float y)
{
	this->body.setPosition(x, y);
}

void Car::update(float deltaTime, float cliffWidth, float groundHeight, float gravity) {	
	sf::Vector2f currentPos = this->body.getPosition();

	if (currentPos.x > cliffWidth && currentPos.y < groundHeight)
	{
		//Height: 1.2, Depth: 1.8, Length: 4.8
		this->force.x = Fdx(this->velocity, this->dragArea, Cdx);
		this->force.y = Fdy(this->velocity, calculateArea(this->carWidth, this->carDepth), this->Cdy) + (gravity * this->mass);
		this->distanceTravel += this->velocity.x * deltaTime;

		std::string distance = std::to_string((int)(this->distanceTravel)) + "m";
		this->distanceText.setString(distance);
	}
	else
	{
		if (currentPos.x > cliffWidth) {
			this->velocity = sf::Vector2f(0.0f, 0.0f);
			this->acceleration = sf::Vector2f(0.0f, 0.0f);
			this->force = sf::Vector2f(0.0f, 0.0f);
			this->frictionForce = 0.0f;
		}
		else {
			this->velocity.y = 0.0f;
			this->force.x = this->engine.getForce() - this->frictionForce + Fdx(this->velocity, this->dragArea, this->Cdx);
		}

	}

	this->engine.setRPM(this->velocity.x);

	this->acceleration = this->force / this->mass;				//a = F / m
	this->velocity += this->acceleration * deltaTime;			//v = v0 + at
	this->body.move(this->velocity * deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->engine.shiftUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->engine.shiftDown();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->engine.accelerate();	//Increases throttle
	else
		this->engine.decelerate();	//Automatic engine braking

	//Make sure the friction force has the correct direction and rests at 0
	if (this->velocity.x > 0.0f)
		this->frictionForce = 0.015f * gravity * this->mass;	//0.015 = rolling friction coefficient
	else if (this->velocity.x < 0.0f)
		this->frictionForce = -0.015f * gravity * this->mass;

	this->updateUI();
}

void Car::draw(sf::RenderWindow* window) {
	window->draw(this->body);
	window->draw(this->rpmMeter);
	window->draw(this->throttleMeter);
	window->draw(this->speedometer);
	window->draw(this->rpmText);
	window->draw(this->distanceText);
}
