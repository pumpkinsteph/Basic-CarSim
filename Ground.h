#pragma once
#include <SFML\Graphics.hpp>
#include <string>

using namespace std;

class Ground {
private:
	sf::Sprite body;
	sf::Texture texture;

	float width;
	float height;
public:
	Ground(string fileName, float width, float height);
	~Ground();

	void changePos(float x, float y);
	float getWidth();
	float getHeight();
	void update(float deltaTime);
	void draw(sf::RenderWindow* window);
};