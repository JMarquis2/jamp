#include "Entity.h"
#include "Interactable.h"
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
Entity::Entity(sf::Vector2f _position, sf::Color _color, int hitboxType, float* hitInfo, float _speed, float _directionAngle) :
    speed(_speed), directionAngle(_directionAngle), Interactable(_position, _color, hitboxType, hitInfo) {
}