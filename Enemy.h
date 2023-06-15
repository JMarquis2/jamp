#pragma once
#include "Unit.h"
#include <SFML/Graphics.hpp>

class Enemy : public Unit {

protected:
	int enemyAtk;
	sf::Color color;
	float collisionDPS;

public:
	~Enemy();
	Enemy();
	Enemy(sf::Vector2f position);
	float getCollisionDPS();
	/*Enemy::chases();*/











};