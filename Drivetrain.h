#pragma once
#include <iostream>

#define PI 3.141592653f
#define NR_OF_GEARS 6

class Drivetrain {
private:
	float finalDriveRatio;
	float rpm;
	float wheelRadius;
	float throttle;
	float gearRatio[NR_OF_GEARS];

	int currentGear;
	int shiftDelay;
	int printDelay;

	bool readyToShift;

	float getTorque();
public:
	Drivetrain();
	~Drivetrain();
	void shiftUp();
	void shiftDown();
	void accelerate();
	void decelerate();
	void setRPM(float speed);
	int getRPM();
	int getGear();
	float getForce();
	float getThrottle();
	void setGear(int gear);

	void printValues(float speed);
};