#include "Healthbar.h"
Healthbar::Healthbar(float _maxHP, float _currentHP, sf::Vector2f position, int _width, int _height) : maxHP(_maxHP), currentHP(_currentHP), width(_width), height(_height){
	this->setPosition(position);

	model = new sf::Vertex[4];
	
	model[0].color = sf::Color::Red;
	model[1].color = sf::Color::Red;
	model[2].color = sf::Color::Red;
	model[3].color = sf::Color::Red;

	model[0].position = sf::Vector2f(0.f, 0.f);
	model[1].position = sf::Vector2f(width, 0.f);
	model[2].position = sf::Vector2f(width, height);
	model[3].position = sf::Vector2f(0.f, height);
}
void Healthbar::setMax(float max) {
	maxHP = max;
}
void Healthbar::setCurrent(float current) {
	currentHP = current;

	float hpRatio = current / maxHP;
	float currentSize = width * hpRatio;

	model[1].position = sf::Vector2f(currentSize, 0.f);
	model[2].position = sf::Vector2f(currentSize, height);
}
void Healthbar::move(sf::Vector2f position) {
	this->setPosition(position);
}
void Healthbar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform = this->getTransform();
	target.draw(model, 4, sf::Quads, states);
}
