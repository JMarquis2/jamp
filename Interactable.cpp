#include "Interactable.h"
#include "collision.h"
Interactable::~Interactable() {};
Interactable::Interactable(bool circHitbox) {
	hitbox = new Hitbox(circHitbox);
}
bool Interactable::collidesWith(Interactable* other) {
	return collides(this->hitbox->getHitShape(), other->hitbox->getHitShape());
}
