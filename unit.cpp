#include "Unit.h"
Unit::~Unit() {

}
Unit::Unit() : Entity(), maxHP(1), currHP(1), maxMana(1), currMana(1), hpRegen(1), manaRegen(1) {
}
Unit::Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,
	float radius, float _speed, float _directionAngle) :
	Entity(_position, radius, _speed, _directionAngle),
	maxHP(_maxHP), currHP(_maxHP), maxMana(_maxMana), currMana(_maxMana), hpRegen(_hpRegen), manaRegen(_manaRegen) {
}
Unit::Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,
	float width, float height, float _speed, float _directionAngle) :
	Entity(_position, width, height, _speed, _directionAngle),
	maxHP(_maxHP), currHP(_maxHP), maxMana(_maxMana), currMana(_maxMana), hpRegen(_hpRegen), manaRegen(_manaRegen) {
}
float Unit::takeDamage(float damage) {
	currHP -= damage;
	if (currHP <= 0)
		return 0.f;
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