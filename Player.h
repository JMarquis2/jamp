#pragma once
#include "Unit.h"
#include <SFML/Graphics.hpp>
class Player : public Unit
{
private:
	sf::CircleShape model;
	sf::Color color;
public:
	~Player();
	Player();
	Player(sf::Vector2f position);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

