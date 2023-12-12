#include "Enemy.h"
#include <iostream>


Enemy::~Enemy() {
	
}

Enemy::Enemy() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f, true, sf::Vector2f(0.f, 0.f), false), color(sf::Color::Red), enemyAtk(5) {
	dimensions.x = 150.f;
	dimensions.y = 150.f;
	collisionDPS = 20.f;
}

Enemy::Enemy(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position, float hitboxWidth, float hitboxHeight,
	float _speed, float _directionAngle, bool _visibleHealth, sf::Vector2f hitboxDisplacement, bool visibleHitbox) : 
	Unit(_maxHP, _maxMana, _hpRegen, _manaRegen, _position, hitboxWidth, hitboxHeight, _speed, _directionAngle, _visibleHealth, hitboxDisplacement, visibleHitbox), enemyAtk(5)
{
	
	dimensions.x = 150.f;
	dimensions.y = 150.f;
	collisionDPS = 20.f;
	//this->getHitbox()->getHitShape()->setPosition(sf::Vector2f(50.f, 0.f));
}
float Enemy::getCollisionDPS() {
	return collisionDPS;
}




