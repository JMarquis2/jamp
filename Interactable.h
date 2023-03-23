#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
class Interactable : public sf::Transformable, public sf::Drawable
{
public:
	bool collidesWith(Interactable* other);
	~Interactable();
	//one for circular hitbox, one for rectangular
	Interactable(sf::Vector2f _position, float hitboxRadius, bool visibleHitbox = false);
	Interactable(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, bool visibleHitbox = false);
	Interactable();
	Hitbox* getHitbox() const;


private:
	Hitbox* hitbox;
	sf::Vector2f position;
};

