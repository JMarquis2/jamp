#include "Hitbox.h"
#include <SFML/Graphics.hpp>
Hitbox::~Hitbox() {
	if (shapeType == 0)
		delete (sf::CircleShape*) hitShape;
	else if (shapeType == 1)
		delete (sf::RectangleShape*) hitShape;
	else
		delete (sf::CircleShape*) hitShape;
}

Hitbox::Hitbox(float* shapeInfo, int _shapeType, bool _isVisible) : shapeType(_shapeType), isVisible(_isVisible){
	if (shapeType == 0) {
		hitShape = new sf::CircleShape(shapeInfo[2]);
		hitShape->setPosition(shapeInfo[0], shapeInfo[1]);

		hitShape->setOutlineColor(sf::Color::Green);
		hitShape->setFillColor(sf::Color::Transparent);
		hitShape->setOutlineThickness(2.f);
	}
	else if (shapeType == 1) {
		hitShape = new sf::RectangleShape(sf::Vector2f(shapeInfo[2], shapeInfo[3]));
		hitShape->setPosition(shapeInfo[0], shapeInfo[1]);
		hitShape->setOutlineColor(sf::Color::Green);
		hitShape->setFillColor(sf::Color::Transparent);
		hitShape->setOutlineThickness(2.f);
	}
	else
		hitShape = new sf::CircleShape(10.f);
}
sf::Shape* Hitbox::getHitShape() const{
	return hitShape;
}
int Hitbox::getShapeType() {
	return shapeType;
}
bool Hitbox::getVisible() {
	return isVisible;
}
