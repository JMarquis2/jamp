#pragma once
#include <SFML/Graphics.hpp>
class Healthbar : public sf::Drawable, public sf::Transformable {
public:
	Healthbar(float _maxHP, float _currentHP, sf::Vector2f position, int _width, int _height);
	void setMax(float max);
	void setCurrent(float current);
	void move(sf::Vector2f position);
private:
	sf::Vertex* model;
	int width;
	int height;
	float maxHP;
	float currentHP;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};