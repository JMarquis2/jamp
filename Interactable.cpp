#include "Interactable.h"
#include "collision.h"
Interactable::~Interactable() {
	delete hitbox;
}
Interactable::Interactable() {
	float tempInfo[] = { 0.f, 0.f, 10.f };
	hitbox = new Hitbox(tempInfo, 0);
	this->setPosition(0.f, 0.f);
}
Interactable::Interactable(sf::Vector2f _position, float hitboxRadius, bool visibleHitbox) {
	float hitInfo[3];
	hitInfo[0] = _position.x;
	hitInfo[1] = _position.y;
	hitInfo[2] = hitboxRadius;
	hitbox = new Hitbox(hitInfo, 0, visibleHitbox);
	this->setPosition(_position);
}
Interactable::Interactable(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, bool visibleHitbox) {
	float hitInfo[4];
	hitInfo[0] = _position.x;
	hitInfo[1] = _position.y;
	hitInfo[2] = hitboxWidth;
	hitInfo[3] = hitboxHeight;
	hitbox = new Hitbox(hitInfo, 1, visibleHitbox);
	this->setPosition(_position);
}
bool Interactable::collidesWith(Interactable* other) {
	return collides(this->hitbox->getHitShape(), other->hitbox->getHitShape());
}
Hitbox* Interactable::getHitbox() const{
	return hitbox;
}
