#pragma once

#include <iostream>
#include <sfml/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	void update(float _deltaTime);
	void draw(sf::RenderWindow& _window);
	sf::RectangleShape getRect();

private:
	sf::RectangleShape player;
	float playerVelocity = 0;
};

