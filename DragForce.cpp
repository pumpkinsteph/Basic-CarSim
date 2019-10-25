#include "DragForce.h"
#include <math.h>

float lenght(sf::Vector2f vec) {
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2)));
}

float calculateArea(float width_in, float depth_in) {
	return (width_in * depth_in);
}

float Fdx(sf::Vector2f velocity_fdx_in, float drag_area_fdx_in, float dragCoefficient_fdx_in) {
	return (-0.5f * airDensity * drag_area_fdx_in * dragCoefficient_fdx_in * lenght(velocity_fdx_in) * velocity_fdx_in.x);
}

float Fdy(sf::Vector2f velocity_fdy_in, float drag_area_fdy_in, float dragCoefficient_fdy_in) {
	return (-0.5f * airDensity * drag_area_fdy_in * dragCoefficient_fdy_in * lenght(velocity_fdy_in) * velocity_fdy_in.y); 
}