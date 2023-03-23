#pragma once
#include <SFML/Graphics.hpp>
class Hitbox
{
public:
	~Hitbox();
	Hitbox(float* shapeInfo, int _shapeType, bool _isVisible = false);
	sf::Shape* getHitShape();
	int getShapeType();
private:
	sf::Shape* hitShape;
	int shapeType;
	bool isVisible;
};

