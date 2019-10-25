#include "Drivetrain.h"

float Drivetrain::getTorque() {
	if (this->throttle < 0.01f)
		return -0.74f * this->rpm / 60;
	else if (this->rpm <= 1000.0f)
		return 220.0f * this->throttle;
	else if (this->rpm < 4600.0f)
		return (0.025f * this->rpm + 195.0f) * this->throttle;
	else if (this->rpm < 7200.0f)
		return (-0.032f * this->rpm + 457.2f) * this->throttle;
	else
		return 0;
}

Drivetrain::Drivetrain() {
	this->finalDriveRatio = 3.44f;
	this->rpm = 1000.0f;
	this->wheelRadius = 0.3186f;
	this->throttle = 0.0f;

	this->currentGear = 0;
	this->shiftDelay = 0;
	this->printDelay = 0;

	this->readyToShift = true;

	this->gearRatio[0] = 3.82f;
	this->gearRatio[1] = 2.20f;
	this->gearRatio[2] = 1.52f;
	this->gearRatio[3] = 1.22f;
	this->gearRatio[4] = 1.02f;
	this->gearRatio[5] = 0.84f;
}

Drivetrain::~Drivetrain() {

}

void Drivetrain::shiftUp() {
	if (!this->readyToShift || this->currentGear >= NR_OF_GEARS - 1)
		return;

	this->rpm = this->rpm * (this->gearRatio[currentGear + 1] / this->gearRatio[currentGear]);
	this->currentGear++;
	this->readyToShift = false;
}

void Drivetrain::shiftDown() {
	if (!this->readyToShift || this->currentGear <= 0)
		return;

	this->rpm = this->rpm * (this->gearRatio[this->currentGear - 1] / this->gearRatio[this->currentGear]);
	this->currentGear--;
	this->readyToShift = false;
}

void Drivetrain::accelerate() {
	if (this->throttle < 0.98f)
		this->throttle += 0.02f;
	else 
		this->throttle = 1.0f;
}

void Drivetrain::decelerate() {
	if (this->throttle > 0.02f)
		this->throttle -= 0.02f;
	else
		this->throttle = 0.0f;
}


void Drivetrain::setRPM(float speed) {
	this->rpm = speed * 60.0f * this->gearRatio[this->currentGear] * this->finalDriveRatio / (2.0f * PI * this->wheelRadius);
}

int Drivetrain::getRPM() {
	return (int)this->rpm;
}

int Drivetrain::getGear() {
	return this->currentGear + 1;
}

float Drivetrain::getForce() {
	if (!this->readyToShift) {
		this->shiftDelay++;
		if (this->shiftDelay > 60) {
			this->readyToShift = true;
			this->shiftDelay = 0;
		}
	}

	return this->gearRatio[this->currentGear] * this->finalDriveRatio * this->getTorque() / this->wheelRadius;
}

float Drivetrain::getThrottle() {
	return this->throttle;
}

void Drivetrain::setGear(int gear) {
	this->currentGear = gear - 1;
}

void Drivetrain::printValues(float speed)
{
	if (this->printDelay == 20)	{
		std::cout << "Gear: " << this->currentGear + 1 << " RPM: " << this->rpm << " Throttle: " << this->throttle 
			<< "\nTorque: " << this->getTorque() << " Force: " << this->getForce() << " Speed: " << speed << "\n\n";
		this->printDelay = 0;
	}

	this->printDelay++;
}


