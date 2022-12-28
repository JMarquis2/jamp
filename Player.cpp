#include "Player.h"
sf::Sprite Player::playerImage;
//this guy right here
sf::Texture Player::playerSheet;
Player::~Player() {
}
Player::Player() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f), color(sf::Color::Cyan), tmodel(sf::CircleShape(50.f)) {
	tmodel.setFillColor(sf::Color::Cyan);
	tmodel.setPosition(0.f, 0.f);
}
Player::Player(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 50.f, 100.f, 0.f), color(sf::Color::Cyan), tmodel(sf::CircleShape(50.f)){
	tmodel.setFillColor(sf::Color::Cyan);
	tmodel.setPosition(position);
}
void Player::loadSpriteFromFile(std::string filename) {
	playerSheet.loadFromFile(filename);
	playerImage.setTexture(playerSheet);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(playerImage, states);
}