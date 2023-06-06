#pragma once
#include "Entity.h"
class Attack : public Entity {
public:
	Attack(int _damage, sf::Time _remainingTime, float angle, sf::Vector2f hitPosition, float width, float height);

	//returns false if deletable
	bool update(sf::Time elapsed);
private:
	int damage;
	sf::Time remainingTime;
};