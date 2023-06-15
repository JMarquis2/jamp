#include "Attack.h"
#include "moves.h"
#include "Entity.h"



class missileAttack : public Attack {
public:
	missileAttack(sf::Time _remainingTime, sf::Vector2f hitPosition, float angle);
	bool update(sf::Time elapsed);


private:
	float velocity;
	sf::Time remainingTime;
	

	




};