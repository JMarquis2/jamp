#include "Player.h"
//this guy right here
Player::~Player() {
}
Player::Player() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f), color(sf::Color::Cyan), tmodel(sf::CircleShape(50.f)) {
	tmodel.setFillColor(sf::Color::Cyan);
	tmodel.setPosition(0.f, 0.f);
}
Player::Player(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 50.f, 100.f, 0.f), color(sf::Color::Cyan), tmodel(sf::CircleShape(50.f)){
	tmodel.setFillColor(sf::Color::Cyan);
	tmodel.setPosition(position);
	vertices = sf::VertexArray(sf::Quads, 4);
	sf::Vector2f pos = this->getPosition();
	vertices[0].position = pos;
	vertices[1].position = sf::Vector2f(pos.x + width, pos.y);
	vertices[2].position = sf::Vector2f(pos.x + width, pos.y + height);
	vertices[3].position = sf::Vector2f(pos.x, pos.y + height);
}
void Player::setTexture(sf::Texture* tex, sf::Vector2i texPos) {
	playerSheet = tex;
	texturePosition.x = texPos.x;
	texturePosition.y = texPos.y;
	vertices[0].texCoords = sf::Vector2f(texturePosition.x, texturePosition.y);
	vertices[1].texCoords = sf::Vector2f(texturePosition.x + width, texturePosition.y);
	vertices[2].texCoords = sf::Vector2f(texturePosition.x + width, texturePosition.y + height);
	vertices[3].texCoords = sf::Vector2f(texturePosition.x, texturePosition.y + height);
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (playerSheet) {
		states.texture = playerSheet;
		states.transform = this->getTransform();
		target.draw(vertices, states);
	}
	else {
		target.draw(tmodel, states);
	}
}