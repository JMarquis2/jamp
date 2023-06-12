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
	//time per attack
	sf::Time attackSpeed;
	//attack cooldown
	sf::Time attackTimer;
public:
	~Player();
	Player();
	Player(sf::Vector2f position);
	Attack* hit(sf::Time elapsed);
	//update debuffs, buffs, attack timers, cooldowns, anything time-related...?
	void update(sf::Time elapsed);
};

