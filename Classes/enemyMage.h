#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "missileAttack.h"

class enemyMage : public Enemy  {

public:
	~enemyMage();
	enemyMage();
	enemyMage(sf::Vector2f position);
	std::list<missileAttack*> homingMissile();

private:

};
