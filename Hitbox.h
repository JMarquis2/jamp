#pragma once
#include <SFML/Graphics.hpp>
class Hitbox
{
public:
	~Hitbox();
	Hitbox(bool circHitbox);
	sf::Shape* getHitShape();
private:
	sf::Shape* hitShape;
	bool isCirc;
};

