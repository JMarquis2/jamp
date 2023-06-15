#include "Attack.h"
#include "Obstacle.h"
#include "Unit.h"
#include "../Helpers/moves.h"
#include <vector>
//#include <typeinfo>
Attack::Attack(int _damage, sf::Time _remainingTime, float angle, sf::Vector2f hitPosition, float width, float height) : Entity(hitPosition, width, height, 0.f, angle, sf::Vector2f(0.f, 0.f), false), damage(_damage), remainingTime(_remainingTime), passThroughObstacles(true), piercing(true) {
	std::vector<int> cardinals = angleToCardinals(angle);
	sf::Vertex* model = new sf::Vertex[4];
	//up
	if (cardinals[0] == 1) {
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;
		
		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(50, 0);
		model[2].position = sf::Vector2f(50, 100);
		model[3].position = sf::Vector2f(0, 100);
	}
	//down
	else if (cardinals[1] == 1) {
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;

		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(50, 0);
		model[2].position = sf::Vector2f(50, 100);
		model[3].position = sf::Vector2f(0, 100);
	}
	//left
	else if (cardinals[2] == 1) {
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;

		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(100, 0);
		model[2].position = sf::Vector2f(100, 50);
		model[3].position = sf::Vector2f(0, 50);
	}
	//right
	else{
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;

		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(100, 0);
		model[2].position = sf::Vector2f(100, 50);
		model[3].position = sf::Vector2f(0, 50);
	}
	setModel(model, 4);
}
bool Attack::update(sf::Time elapsed) {
	remainingTime -= elapsed;
	if (remainingTime <= sf::milliseconds(0))
		return false;
	return true;
}
//hits functions return false if attack should be deleted
bool Attack::hits(Unit* target) {
	//this is the case where the attack is already hitting the target.
	if (currentlyHitting.find((*target).getID()) != currentlyHitting.end()) {
		return true;
	}
	//this is the case where the attack is hitting the target for the first time.
	else {
		currentlyHitting.insert((*target).getID());
		((Unit*)target)->takeDamage(damage);
		if (piercing)
			return true;
		else
			return false;
	}
}
bool Attack::hits(Obstacle* target) {
	return passThroughObstacles;
}
int Attack::getDamage() {
	return damage;
}
