#include "Interactable.h"
#include "collision.h"
Interactable::~Interactable() {
	delete hitbox;
}
Interactable::Interactable() {
	float tempInfo[] = { 0.f, 0.f, 10.f };
	hitbox = new Hitbox(tempInfo, 0);
	position = sf::Vector2f(0.f, 0.f);
}
Interactable::Interactable(sf::Vector2f _position, float radius) {
	float hitInfo[3];
	hitInfo[0] = _position.x;
	hitInfo[1] = _position.y;
	hitInfo[2] = radius;
	hitbox = new Hitbox(hitInfo, 0);
	position = _position;
}
Interactable::Interactable(sf::Vector2f _position, float width, float height) {
	float hitInfo[4];
	hitInfo[0] = _position.x;
	hitInfo[1] = _position.y;
	hitInfo[2] = width;
	hitInfo[3] = height;
	hitbox = new Hitbox(hitInfo, 1);
	position = _position;
}
bool Interactable::collidesWith(Interactable* other) {
	return collides(this->hitbox->getHitShape(), other->hitbox->getHitShape());
}
