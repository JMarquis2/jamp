#include "Unit.h"
#include <SFML/Graphics.hpp>

class Enemy : public Unit {

protected:
	int enemyHP;
	int enemyAtk;
	sf::Color color;

public:
	~Enemy();
	Enemy();
	Enemy(sf::Vector2f position);
	/*Enemy::chases();*/











};