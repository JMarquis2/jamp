#include "Hitbox.h"
#include <SFML/Graphics.hpp>
Hitbox::~Hitbox() {
	if (shapeType == 0)
		delete (sf::CircleShape*) hitShape;
	else if(shapeType == 1)
		delete (sf::RectangleShape*) hitShape;
}
Hitbox::Hitbox(float* shapeInfo, int _shapeType) {
	if (shapeType == 0) {
		hitShape = new sf::CircleShape(shapeInfo[2]);
		hitShape->setPosition(shapeInfo[0], shapeInfo[1]);
	}
	else if (shapeType == 1) {
		hitShape = new sf::RectangleShape(sf::Vector2f(shapeInfo[2], shapeInfo[3]));
		hitShape->setPosition(shapeInfo[0], shapeInfo[1]);
	}
	shapeType = _shapeType;
}
sf::Shape* Hitbox::getHitShape() {
	return hitShape;
}
int Hitbox::getShapeType() {
	return shapeType;
}
