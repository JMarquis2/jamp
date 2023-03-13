#include "Player.h"
#include <cmath>
//this guy right here
Player::~Player() {
	delete[] model;
}
Player::Player() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f), color(sf::Color::Cyan), defaultModel(sf::CircleShape(50.f)) {
	defaultModel.setFillColor(sf::Color::Cyan);
	defaultModel.setPosition(0.f, 0.f);
	playerSheet = nullptr;
	model = nullptr;
}
Player::Player(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 50.f, 100.f, 0.f), color(sf::Color::Cyan), defaultModel(sf::CircleShape(50.f)){
	defaultModel.setFillColor(sf::Color::Cyan);
	defaultModel.setPosition(position);
	model = new sf::Vertex[4];
	sf::Vector2f pos = this->getPosition();
	model[0].position = pos;
	model[1].position = sf::Vector2f(pos.x + width, pos.y);
	model[2].position = sf::Vector2f(pos.x + width, pos.y + height);
	model[3].position = sf::Vector2f(pos.x, pos.y + height);
	playerSheet = nullptr;
}
void Player::setTexture(sf::Texture* tex, sf::Vector2i texPos) {
	playerSheet = tex;
	updateTexture(texPos);
}
//for some reason, when this is called, the player object doesnt have its correct member values. I suspect its a problem with a copy constructor
//or assignment operator or something.
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (playerSheet) {
		states.texture = playerSheet;
		states.transform = this->getTransform();
		target.draw(model, 4, sf::Quads, states);
		//target.draw(vertices, states);
	}
	else {
		target.draw(defaultModel, states);
	}
}
void Player::updateTexture(sf::Vector2i texPos) {
	texturePosition.x = texPos.x;
	texturePosition.y = texPos.y;
	model[0].texCoords = sf::Vector2f(texturePosition.x, texturePosition.y);
	model[1].texCoords = sf::Vector2f(texturePosition.x + width, texturePosition.y);
	model[2].texCoords = sf::Vector2f(texturePosition.x + width, texturePosition.y + height);
	model[3].texCoords = sf::Vector2f(texturePosition.x, texturePosition.y + height);
}