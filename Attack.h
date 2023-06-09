#pragma once
#include "Unit.h"
#include "Obstacle.h"
#include <unordered_set>
class Attack : public Entity {
public:
	Attack(int _damage, sf::Time _remainingTime, float angle, sf::Vector2f hitPosition, float width, float height);

	//returns false if deletable
	bool update(sf::Time elapsed);
	int getDamage();

	//returns false if deletable
	bool hits(Unit* target);
	bool hits(Obstacle* target);
private:
	bool passThroughObstacles;
	bool piercing;
	std::unordered_set<int> currentlyHitting;
	int damage;
	sf::Time remainingTime;
};