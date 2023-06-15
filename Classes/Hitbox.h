#pragma once
#include <SFML/Graphics.hpp>
class Hitbox
{
public:
	~Hitbox();
	Hitbox(float* shapeInfo, int _shapeType, bool _isVisible = false);
	sf::Shape* getHitShape() const;
	int getShapeType();
	bool getVisible();
	void setVisible(bool visible);
private:
	sf::Shape* hitShape;
	int shapeType;
	bool isVisible;
};

