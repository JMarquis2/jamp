#include "Entity.h"
#include "Interactable.h"
#include "moves.h"
#include <iostream>
Entity::~Entity() {
}
Entity::Entity() : speed(0.f), directionAngle(0.f), Interactable(){

}
float Entity::getAngle() {
    return directionAngle;
}
float Entity::getSpeed() {
    return speed;
}
void Entity::setSpeed(float _speed) {
    speed = _speed;
}
void Entity::setAngle(float _angle) {
    directionAngle = _angle;
}
void Entity::setAngle(int* directions) {
    directionAngle = cardinalsToAngle(directions);
}
void Entity::setIdle(bool _isIdle) {
    isIdle = _isIdle;
}
bool Entity::getIdle() {
    return isIdle;
}
Entity::Entity(sf::Vector2f _position, float hitboxRadius, float _speed, float _directionAngle, bool visibleHitbox) :
    speed(_speed), directionAngle(_directionAngle), isIdle(true), Interactable(_position, hitboxRadius, visibleHitbox) {
}
Entity::Entity(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, float _speed, float _directionAngle, bool visibleHitbox) :
    speed(_speed), directionAngle(_directionAngle), isIdle(true), Interactable(_position, hitboxWidth, hitboxHeight, visibleHitbox) {
}
void Entity::moveToPosition(sf::Vector2f position) {
    sf::Vector2f posDiff(this->getPosition());
    posDiff.x = position.x - posDiff.x;
    posDiff.y = position.y - posDiff.y;
    this->setPosition(position);
    this->getHitbox()->getHitShape()->move(posDiff);
}
void Entity::setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texCoords) {
	importTexture(textureInfo);
	sf::Vertex* model = new sf::Vertex[4];
	setTextureModel(model, 4);
	setTexturePosition(sf::Vector2i(0, 0));
	setTextureCoords(texCoords);
}
void Entity::updateTexture() {
	//right now this is how I'll deal with idle animation. In the future, we would have an idle animation, too.
	if (this->isIdle) {
		return;
	}
	std::vector<int> facing = angleToCardinals(this->getAngle());
	int newX = 0;
	int newY = 0;
	sf::Vector2i dimensions = getTextureDimensions();
	if (facing[2] == 1) {
		newY = 1;
	}
	else if (facing[3] == 1) {
		newY = 0;
	}
	else if (facing[0] == 1) {
		newY = 3;
	}
	else {
		newY = 2;
	}
	newX = (getTexturePosition().x + dimensions.x) % (getFrameNumbers()->at(newY) * dimensions.x);
	newY *= dimensions.y;
	setTextureCoords(sf::Vector2i(newX, newY));
}

