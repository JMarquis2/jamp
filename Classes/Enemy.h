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

	float getCollisionDPS();
	Enemy(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,float hitboxWidth, float hitboxHeight,
		float _speed, float _directionAngle, bool _visibleHealth, sf::Vector2f hitboxDisplacement, bool visibleHitbox);
	/*Enemy::chases();*/
};