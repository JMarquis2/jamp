#include "Enemy.h"
#include <iostream>


Enemy::~Enemy() {
	
}

Enemy::Enemy() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f, true, sf::Vector2f(0.f, 0.f), false), color(sf::Color::Red), enemyAtk(5) {
	dimensions.x = 150.f;
	dimensions.y = 150.f;
	collisionDPS = 20.f;
}

Enemy::Enemy(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 50.f, 150.f, 50.f, 0.f, true, sf::Vector2f(50.f, 0.f), true), color(sf::Color::Red), enemyAtk(5) {
	dimensions.x = 150.f;
	dimensions.y = 150.f;
	collisionDPS = 20.f;
	//this->getHitbox()->getHitShape()->setPosition(sf::Vector2f(50.f, 0.f));
}
float Enemy::getCollisionDPS() {
	return collisionDPS;
}






