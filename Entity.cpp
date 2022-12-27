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
Entity::Entity(sf::Vector2f _position, float radius, float _speed, float _directionAngle) :
    speed(_speed), directionAngle(_directionAngle), Interactable(_position, radius) {
}
Entity::Entity(sf::Vector2f _position, float width, float height, float _speed, float _directionAngle) :
    speed(_speed), directionAngle(_directionAngle), Interactable(_position, width, height) {
}

