#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
class Interactable : public sf::Transformable, public sf::Drawable
{
public:
	bool collidesWith(Interactable* other);
	~Interactable();
	//transformableType determines the kind of hitbox that the interactable will have, 0 is circle, 1 is rectangle, more added in future
	Interactable(sf::Vector2f _position, sf::Color _color, int hitboxType, float* hitInfo);
	Interactable();


private:
	Hitbox* hitbox;
	sf::Color color;
	sf::Vector2f position;
};

