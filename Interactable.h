#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
class Interactable : public sf::Transformable, public sf::Drawable
{
public:
	bool collidesWith(Interactable* other);
	virtual ~Interactable();
	Interactable(bool circHitbox);

private:
	Hitbox* hitbox;
};

