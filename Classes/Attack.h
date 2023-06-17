#pragma once
#include "Unit.h"
#include "Obstacle.h"
#include <unordered_set>
class Attack : public Entity {
public:
	Attack(int _damage, sf::Time _remainingTime, float angle, sf::Vector2f hitPosition, float width, float height, float speed, bool passing, bool piercing,
		sf::Vector2f hitboxDisplacement, bool visibleHitbox);
	Attack(int _damage, sf::Time _remainingTime, sf::Vector2f hitPosition, float angle, float radius, float speed, bool passing, bool piercing,
		sf::Vector2f hitBoxDisplacement, bool visibleHitbox); //circluar attacks for future work

	//returns false if deletable
	virtual bool update(sf::Time elapsed);

	int getDamage();
	bool hits(Unit* target);
	bool hits(Obstacle* target);

private:
	bool passThroughObstacles;
	bool piercing;
	std::unordered_set<int> currentlyHitting;
	int damage;
	sf::Time remainingTime;
};