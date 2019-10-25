#pragma once
#include <SFML/Graphics.hpp>

	static const float airDensity = 1.22f;

	float calculateArea(float width_in, float depth_in);
	float lenght(sf::Vector2f vec);
	float Fdx(sf::Vector2f velocity_fdx_in, float drag_area_fdx_in, float dragCoefficient_fdx_in);
	float Fdy(sf::Vector2f velocity_fdy_in, float drag_area_fdy_in, float dragCoefficient_fdy_in);
