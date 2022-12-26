#pragma once
#include "Interactable.h"
#include <SFML/Graphics.hpp>
class Entity : public Interactable
{
public:
	 ~Entity();
	 Entity();
	 Entity(sf::Vector2f _position, sf::Color _color, int hitboxType, float* hitInfo, float _speed, float _directionAngle);
	 float getSpeed();
	 float getAngle();
private:
	float speed;
	float directionAngle;
};

