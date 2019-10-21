#include "Car.h"

Car::Car(string fileName, float width, float height, float weight) {
	this->texture.loadFromFile(fileName);
	this->body.setTexture(this->texture);

	this->speedX = 0.0f;
	this->speedY = 0.0f;
	this->frictionForce = 0.0f;
	this->acceleration = 0.0f;
	this->forceX = 0.0f;
	this->mass = weight;
	this->width = width;
	this->height = height;

	this->rpmMeter.setPosition(400.0f, 25.0f);
	this->rpmMeter.setSize(sf::Vector2f(100.0f, 30.0f));
	this->rpmMeter.setFillColor(sf::Color::Black);

	this->throttleMeter.setPosition(50.0f, 25.0f);
	this->throttleMeter.setSize(sf::Vector2f(20.0f, 5.0f));
	this->throttleMeter.setFillColor(sf::Color::White);

	this->throttleBack.setPosition(50.0f, 25.0f);
	this->throttleBack.setSize(sf::Vector2f(100.0f, 20.0f));
	this->throttleBack.setFillColor(sf::Color::White);

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
}

Car::~Car() {

}

void Car::changePos(float x, float y) {
	this->body.setPosition(x, y);
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
	return this->mass*gravity*sin(slopeAngle)*deltaTime;
}

void Car::reset(float x, float y) {
	this->changePos(x, y);
	this->speedX = 0.0f;
	this->speedY = 0.0f;
	this->frictionForce = 0.0f;
	this->acceleration = 0.0f;
	this->forceX = 0.0f;
}

void Car::update(float deltaTime, float cliffWidth, float groundHeight, float gravity) {	
	sf::Vector2f currentPos = this->body.getPosition();

	if (currentPos.x > cliffWidth && currentPos.y < groundHeight) {
		this->speedY += gravity * deltaTime;
		body.move(0.0f, this->speedY * deltaTime);
		this->forceX = 0.0f;							//Change this when adding air resistance
	}
	else {
		this->forceX = this->engine.getForce() - this->frictionForce;
		this->engine.setRPM(this->speedX);
	}

	/*
	Det finns 3 fall:
	- på klippan när den är 0 <= x <= cliffWidth och y = 300 - carheight()
	- när den faller från klippan x > cliffWidth och 300 - carheight() <= y < groundHeight
	- när den träffar marken x > cliffWidth och y = groundHeight
	*/

	this->acceleration = this->forceX / this->mass;		//a = F / m
	this->speedX += acceleration * deltaTime;			//v = v0 + at
	this->body.move(this->speedX * deltaTime, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->engine.shiftUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->engine.shiftDown();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->engine.accelerate();	//Increases throttle
	else
		this->engine.decelerate();	//Automatic engine braking

	//Change make sure the friction force has the correct direction and rests at 0
	if (this->speedX > 0.0f)
		this->frictionForce = 0.015f * gravity * this->mass;	//0.015 = rolling friction coefficient
	else if (this->speedX < 0.0f)
		this->frictionForce = -0.015f * gravity * this->mass;


	/* ------------------- UI stuff ---------------------- */
	int rpmColour = (int)((float)engine.getRPM() * (255.0f / 7500.0f));
	this->rpmMeter.setFillColor(sf::Color(rpmColour, 255 - rpmColour, 0));
	this->rpmMeter.setSize(sf::Vector2f(this->engine.getRPM() * 500.0f / 7500.0f, 30.0f));

	this->throttleMeter.setSize(sf::Vector2f(this->engine.getThrottle() * 100.0f, 20.0f));

	std::string speed = "Speed:   " + std::to_string((int)(this->speedX * 3.6f)) + " km/h";
	this->speedometer.setString(speed);
	std::string revs = "Gear: " + std::to_string(this->engine.getGear()) + "       RPM: " + std::to_string(this->engine.getRPM());
	this->rpmText.setString(revs);

	this->engine.printValues(this->speedX);

	/*
	if on a slope
		apply gravity Rolling
	*/
}

void Car::draw(sf::RenderWindow* window) {
	window->draw(this->body);
	window->draw(this->rpmMeter);
	//window->draw(this->throttleBack);
	window->draw(this->throttleMeter);
	window->draw(this->speedometer);
	window->draw(this->rpmText);
}
