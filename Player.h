#pragma once
#include "Unit.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Attack.h"
class Player : public Unit
{
private:
	sf::Color color;
	int attackPower;
public:
	~Player();
	Player();
	Player(sf::Vector2f position);
	void updateTexturePlayer(bool isIdle);
	Attack* hit();
};

