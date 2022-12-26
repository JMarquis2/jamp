#include "Interactable.h"
#include "collision.h"
Interactable::~Interactable() {
	delete hitbox;
}
Interactable::Interactable() {
	float tempInfo[] = { 0.f, 0.f, 10.f };
	hitbox = new Hitbox(tempInfo, 0);
	color = sf::Color::Magenta;
	position = sf::Vector2f(0.f, 0.f);
}
Interactable::Interactable(sf::Vector2f _position, sf::Color _color, int hitboxType, float* hitInfo) {
	hitbox = new Hitbox(hitInfo, hitboxType);
	color = _color;
	position = _position;
}
bool Interactable::collidesWith(Interactable* other) {
	return collides(this->hitbox->getHitShape(), other->hitbox->getHitShape());
}
