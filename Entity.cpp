#include "Entity.h"
#include "Interactable.h"
#include "moves.h"
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

