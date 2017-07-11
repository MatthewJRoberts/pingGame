#pragma once

#include <iostream>
#include <sfml/Graphics.hpp>

class Ball
{
public:
	Ball();
	~Ball();

	void update(float _deltaTime, sf::RectangleShape player, int& _score);
	void draw(sf::RenderWindow& _window);

	bool isOver = false;

private:
	sf::RectangleShape ball;
	float velX = 350.0f;
	float velY = 350.0f;
};

