#pragma once
#include "Interactable.h"
#include <SFML/Graphics.hpp>
class Entity : public Interactable
{
public:
	 ~Entity();
	 Entity();
	 Entity(sf::Vector2f _position, float radius, float _speed, float _directionAngle);
	 Entity(sf::Vector2f _position, float width, float height, float _speed, float _directionAngle);
	 void moveToPosition(sf::Vector2f position);

	 float getSpeed();
	 float getAngle();

	 void setSpeed(float _speed);
	 void setAngle(float _angle);
private:
	float speed;
	float directionAngle;
};

