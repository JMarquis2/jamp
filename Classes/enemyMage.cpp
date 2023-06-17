#include "enemyMage.h"
#include "../Helpers/moves.h"
#include <iostream>


enemyMage::~enemyMage() {}

enemyMage::enemyMage() {

}

enemyMage::enemyMage(sf::Vector2f position) : Enemy(50, 0, 0, 0, position, 100, 100, 100, 270, true, sf::Vector2f(50,100), true){

}

std::list<missileAttack*> enemyMage::homingMissile(){
	std::list<missileAttack*> missileList;
	std::vector<int> cardinals = angleToCardinals(this->getAngle());
	sf::Vector2f hitPosition = this->getPosition();
	//up
	if (cardinals[0] == 1) {

		hitPosition.x += 25;
		hitPosition.y -= 100;
	}
	//down
	else if (cardinals[1] == 1) {

		hitPosition.x += 25;
		hitPosition.y += 100;
	}
	//left
	else if (cardinals[2] == 1) {

		hitPosition.x -= 100;
		hitPosition.y += 25;
	}
	//right
	else if (cardinals[3] == 1) {

		hitPosition.x += 100;
		hitPosition.y += 25;
	}
	
	missileList.push_back(new missileAttack(sf::seconds(10), this->getPosition(), this->getAngle()));
	missileList.push_back(new missileAttack(sf::seconds(10), this->getPosition(), this->getAngle() + 90));
	missileList.push_back(new missileAttack(sf::seconds(10), this->getPosition(), this->getAngle() - 90));
	
	
	return missileList;
}
