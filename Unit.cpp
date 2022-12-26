#include "Unit.h"
Unit::~Unit() {

}
Unit::Unit() : Entity(), maxHP(1), currHP(1), maxMana(1), currMana(1), hpRegen(1), manaRegen(1) {
}
Unit::Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position, sf::Color _color,
    int hitboxType, float* hitInfo, float _speed, float _directionAngle) :
    Entity(_position, _color, hitboxType, hitInfo, _speed, _directionAngle),
    maxHP(_maxHP), currHP(_maxHP), maxMana(_maxMana), currMana(_maxMana), hpRegen(_hpRegen), manaRegen(_manaRegen){
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
void Unit::regenHP(float seconds) {
	currHP += (hpRegen * seconds);
	if (currHP > maxHP)
		currHP = maxHP;
}