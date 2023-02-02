#pragma once
#include <SFML/Graphics.hpp>
class Hitbox
{
public:
	~Hitbox();
	Hitbox(float* shapeInfo, int _shapeType);
	sf::Shape* getHitShape();
	int getShapeType();
private:
	sf::Shape* hitShape;
	int shapeType;
};

