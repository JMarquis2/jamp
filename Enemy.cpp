#include "Enemy.h"
#include <iostream>


Enemy::~Enemy() {
	
}

Enemy::Enemy() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f), color(sf::Color::Red), enemyAtk(5), enemyHP(100) {

}

Enemy::Enemy(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 25.f, 50.f, 0.f, true), color(sf::Color::Red), enemyAtk(5), enemyHP(100) {
	dimensions.x = 150.f;
	dimensions.y = 150.f;

}






