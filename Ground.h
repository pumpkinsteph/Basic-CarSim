#pragma once
#include <SFML\Graphics.hpp>

class Ground {
private:
	sf::RectangleShape body;
	sf::Texture texture;

	float width;
	float height;
public:
	Ground(float width, float height);
	~Ground();

	void changePos(float x, float y);
	float getWidth();
	float getHeight();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
};