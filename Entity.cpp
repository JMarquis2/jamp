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
Entity::Entity(sf::Vector2f _position, float radius, float _speed, float _directionAngle) :
    speed(_speed), directionAngle(_directionAngle), isIdle(true), Interactable(_position, radius) {
}
Entity::Entity(sf::Vector2f _position, float width, float height, float _speed, float _directionAngle) :
    speed(_speed), directionAngle(_directionAngle), isIdle(true), Interactable(_position, width, height) {
}
void Entity::moveToPosition(sf::Vector2f position) {
    this->setPosition(position);
    this->getHitbox()->getHitShape()->setPosition(position);
}

