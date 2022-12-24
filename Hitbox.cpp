#include "Hitbox.h"
#include <SFML/Graphics.hpp>
Hitbox::~Hitbox() {
	if (isCirc)
		delete (sf::CircleShape*) hitShape;
	else
		delete (sf::RectangleShape*) hitShape;
}
Hitbox::Hitbox(bool circHitbox) {
	isCirc = circHitbox;
	if (circHitbox) {
		hitShape = new sf::CircleShape();
	}
	else {
		hitShape = new sf::RectangleShape();
	}
}
sf::Shape* Hitbox::getHitShape() {
	return hitShape;
}
