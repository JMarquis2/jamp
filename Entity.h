#pragma once
#include "Interactable.h"
#include <SFML/Graphics.hpp>
class Entity : public Interactable
{
public:
	 ~Entity();
	 Entity();
	 Entity(sf::Vector2f _position, float radius, float _speed, float _directionAngle, bool visibleHitbox = false);
	 Entity(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, float _speed, float _directionAngle, bool visibleHitbox = false);
	 void moveToPosition(sf::Vector2f position);

	 float getSpeed();
	 float getAngle();
	 bool getIdle();

	 void setSpeed(float _speed);
	 void setAngle(float _angle);
	 void setAngle(int* directions);
	 void setIdle(bool _isIdle);
	 void updateTexture();
private:
	float speed;
	float directionAngle;
	bool isIdle;
};

