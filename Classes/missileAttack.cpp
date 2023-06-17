#include "missileAttack.h"
#include "../Helpers/moves.h"
#include "Entity.h"



missileAttack::missileAttack(sf::Time _remainingTime, sf::Vector2f hitPosition, float angle) : Attack(10, _remainingTime, angle, hitPosition, 80, 20, 50, false, false, sf::Vector2f(10, 10), true), remainingTime(_remainingTime) {


}

bool missileAttack::update(sf::Time elapsed){
	
	remainingTime -= elapsed;
	if ( remainingTime <= sf::milliseconds(0))
		return false;
	return true;
}






