#pragma once
#include "Entity.h"
class Unit : public Entity
{
public:
	Unit();
	Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen,
		sf::Vector2f _position, sf::Color _color, int hitboxType, float* hitInfo, float _speed, float _directionAngle);
	~Unit();
	float getCurrHP();
	float takeDamage(float damage);
	void regenHP(float seconds);

private:
	//additional potential stats like damage, armor, mr, cdr, whatever...
	//regens are per second
	float currHP;
	float maxHP;
	float currMana;
	float maxMana;
	float hpRegen;
	float manaRegen;
	//needed: list of buffs, list of debuffs
};

