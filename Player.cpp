#include "Player.h"
Player::~Player() {
}
Player::Player() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f), color(sf::Color::Cyan), model(sf::CircleShape(50.f)) {
	model.setFillColor(sf::Color::Cyan);
	model.setPosition(0.f, 0.f);
}
Player::Player(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 50.f, 100.f, 0.f), color(sf::Color::Cyan), model(sf::CircleShape(50.f)){
	model.setFillColor(sf::Color::Cyan);
	model.setPosition(position);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(model, states);
}