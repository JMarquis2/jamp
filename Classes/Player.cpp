#include "Player.h"
#include <cmath>
#include "../Helpers/moves.h"
#include <iostream>
Player::~Player() {
}
Player::Player() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f, true, sf::Vector2f(25.f, 50.f), false), color(sf::Color::Cyan), attackPower(20), attackSpeed(sf::seconds(0.2f)), attackTimer(sf::seconds(0.f)) {
}
Player::Player(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 25.f, 50.f, 0.f, true, sf::Vector2f(25.f, 50.f), true), color(sf::Color::Cyan), attackPower(20), attackSpeed(sf::seconds(0.2f)), attackTimer(sf::seconds(0.f)) {
	dimensions.x = 100.f;
	dimensions.y = 100.f;
}
Attack* Player::hit() {
	if (attackTimer >= sf::seconds(0.f))
		return nullptr;
	std::vector<int> cardinals = angleToCardinals(this->getAngle());

	float hitWidth = 0;
	float hitHeight = 0;
	sf::Vector2f hitPosition = this->getPosition();
	//up
	if (cardinals[0] == 1) {
		hitWidth = 50;
		hitHeight = 100;
		hitPosition.x += 25;
		hitPosition.y -= 100;
	}
	//down
	else if (cardinals[1] == 1) {
		hitWidth = 50;
		hitHeight = 100;
		hitPosition.x += 25;
		hitPosition.y += 100;
	}
	//left
	else if (cardinals[2] == 1) {
		hitWidth = 100;
		hitHeight = 50;
		hitPosition.x -= 100;
		hitPosition.y += 25;
	}
	//right
	else if (cardinals[3] == 1) {
		hitWidth = 100;
		hitHeight = 50;
		hitPosition.x += 100;
		hitPosition.y += 25;
	}
	Attack* tempAttack = new Attack(attackPower, sf::milliseconds(100), this->getAngle(), hitPosition, hitWidth, hitHeight, 0, sf::Vector2f(0, 0), false);
	attackTimer = attackSpeed;
	return tempAttack;
}
void Player::update(sf::Time elapsed) {
	attackTimer -= elapsed;
	return tempAttack;
}

void Player::updateTexturePlayer(bool isIdle) {
	//right now this is how I'll deal with idle animation. In the future, we would have an idle animation, too.
	if (isIdle) {
		return;
	}
	std::vector<int> facing = angleToCardinals(this->getAngle());
	int newX = 0;
	int newY = 0;
	sf::Vector2i dimensions = getTextureDimensions();
	//left
	if (facing[2] == 1) {
		newY = 0;
	}
	// right
	else if (facing[3] == 1) {
		newY = 1;
	}
	// up
	else if (facing[0] == 1) {
		newY = 2;
	}
	//down
	else {
		newY = 3;
	}
	newX = (getTexturePosition().x + dimensions.x) % (getFrameNumbers()->at(newY) * dimensions.x);
	newY *= dimensions.y;
	setTextureCoords(sf::Vector2i(newX, newY));
}