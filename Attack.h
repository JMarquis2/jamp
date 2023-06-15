#pragma once
#include "Entity.h"
class Attack : public Entity {
public:
	Attack(int _damage, sf::Time _remainingTime, float angle, sf::Vector2f hitPosition, float width, float height, float speed, sf::Vector2f hitboxDisplacement, bool visibleHitbox);
	Attack(int _damage, sf::Time _remainingTime, sf::Vector2f hitPosition, float angle, float radius, float speed, sf::Vector2f hitBoxDisplacement, bool visibleHitbox); //circluar attacks for future work

	//returns false if deletable
	virtual bool update(sf::Time elapsed);
private:
	int damage;
	sf::Time remainingTime;
};