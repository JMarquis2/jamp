#pragma once
#include "Entity.h"
#include <list>
class Unit : public Entity
{
public:
	Unit();
	Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,
		float hitboxRadius, float _speed, float _directionAngle, bool visibleHitbox = false);
	Unit(float _maxHP, float _maxMana, float _hpRegen, float _manaRegen, sf::Vector2f _position,
		float hitboxWidth, float hitboxHeight, float _speed, float _directionAngle, bool visibleHitbox = false);
	~Unit();
	float getCurrHP();
	float takeDamage(float damage);
	void regen(float seconds);

private:
	//additional potential stats like damage, armor, mr, cdr, whatever...
	//regens are per second
	float currHP;
	float maxHP;
	float currMana;
	float maxMana;
	float hpRegen;
	float manaRegen;
	//needed: list of buffs, list of debuffs. Maybe not. Maybe a better way to do buffs and debuffs is to have a list of buffs and a list of debuffs in the main program,
	//which has pointers to the classes that it changes. Maybe mix of the 2??
	//std::list<Buff> buffs;
	//std::list<Debuff> debuffs;
};
