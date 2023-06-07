#include "Unit.h"
Unit::~Unit() {
	delete healthbar;
}
Unit::Unit() : Entity(), visibleHealth(true), maxHP(1), currHP(1), maxMana(1), currMana(1), hpRegen(1), manaRegen(1) {
	healthbar = new Healthbar(1, 1, sf::Vector2f(this->getPosition().x, this->getPosition().y + this->dimensions.y), this->dimensions.x, 10);
}
Unit::Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,
	float hitboxRadius, float _speed, float _directionAngle, bool _visibleHealth, sf::Vector2f hitboxDisplacement, bool visibleHitbox) :
	Entity(_position, hitboxRadius, _speed, _directionAngle, hitboxDisplacement, visibleHitbox),
	visibleHealth(_visibleHealth), maxHP(_maxHP), currHP(_maxHP), maxMana(_maxMana), currMana(_maxMana), hpRegen(_hpRegen), manaRegen(_manaRegen) {
	healthbar = new Healthbar(_maxHP, _maxHP, sf::Vector2f(this->getHitbox()->getHitShape()->getPosition().x, this->getHitbox()->getHitShape()->getPosition().y + hitboxRadius * 2 + 3), hitboxRadius * 2, 10);
}
Unit::Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,
	float hitboxWidth, float hitboxHeight, float _speed, float _directionAngle, bool _visibleHealth, sf::Vector2f hitboxDisplacement, bool visibleHitbox) :
	Entity(_position, hitboxWidth, hitboxHeight, _speed, _directionAngle, hitboxDisplacement, visibleHitbox),
	visibleHealth(_visibleHealth), maxHP(_maxHP), currHP(_maxHP), maxMana(_maxMana), currMana(_maxMana), hpRegen(_hpRegen), manaRegen(_manaRegen) {
	healthbar = new Healthbar(_maxHP, _maxHP, sf::Vector2f(this->getHitbox()->getHitShape()->getPosition().x, this->getHitbox()->getHitShape()->getPosition().y + hitboxHeight + 3), hitboxWidth, 10);
}
float Unit::takeDamage(float damage) {
	currHP -= damage;
	if (currHP <= 0)
		return 0.f;
	healthbar->setCurrent(currHP);
	return currHP;
}
float Unit::getCurrHP() {
	return currHP;
}
void Unit::regen(float seconds) {
	currHP += (hpRegen * seconds);
	if (currHP > maxHP)
		currHP = maxHP;
	currMana += (manaRegen * seconds);
	if (currMana > maxMana)
		currMana = maxMana;
}
void Unit::moveToPosition(sf::Vector2f position) {
	healthbar->move(sf::Vector2f(this->getHitbox()->getHitShape()->getPosition().x , position.y + dimensions.y + 3));
	Entity::moveToPosition(position);
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*healthbar);
	Interactable::draw(target, states);
}