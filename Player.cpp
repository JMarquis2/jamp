#include "Player.h"
#include <cmath>
#include "moves.h"
#include <iostream>
//this guy right here
Player::~Player() {
	delete[] model;
}
Player::Player() : Unit(100.f, 100.f, 5.f, 5.f, sf::Vector2f(0.f, 0.f), 50.f, 100.f, 100.f, 0.f), texHeight(0), texWidth(0), color(sf::Color::Cyan) {
	playerSheet = nullptr;
	model = nullptr;
}
Player::Player(sf::Vector2f position) : Unit(100.f, 100.f, 5.f, 5.f, position, 25.f, 50.f, 0.f, true), texHeight(0), texWidth(0), color(sf::Color::Cyan){
	model = new sf::Vertex[4];
	model[0].position = sf::Vector2f(0.f, 0.f);
	model[1].position = sf::Vector2f(width, 0.f);
	model[2].position = sf::Vector2f(width, height);
	model[3].position = sf::Vector2f(0.f, height);
	playerSheet = nullptr;

	//temporary? this should probably be done in another way...
	this->getHitbox()->getHitShape()->setPosition(sf::Vector2f(position.x + 25.f, position.y + 50.f));
}
void Player::setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos) {
	playerSheet = textureInfo.second;
	texWidth = textureInfo.first->at(0);
	texHeight = textureInfo.first->at(1);
	for (int i = 0; i < textureInfo.first->at(2); i++) {
		frameNumbers.push_back(textureInfo.first->at(i + 3));
	}
	setTexturePosition(texPos);
}
//for some reason, when this is called, the player object doesnt have its correct member values. I suspect its a problem with a copy constructor
//or assignment operator or something.
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (playerSheet) {
		target.draw(*(getHitbox()->getHitShape()), states);
		states.texture = playerSheet;
		states.transform = this->getTransform();
		target.draw(model, 4, sf::Quads, states); 
		//target.draw(vertices, states);
	}
	else {
		std::cout << "error: no sprite set for Player class" << std::endl;
	}
}
void Player::setTexturePosition(sf::Vector2i texPos) {
	texturePosition.x = texPos.x;
	texturePosition.y = texPos.y;
	model[0].texCoords = sf::Vector2f((float) texturePosition.x, (float) texturePosition.y);
	model[1].texCoords = sf::Vector2f((float) texturePosition.x + width, (float) texturePosition.y);
	model[2].texCoords = sf::Vector2f((float) texturePosition.x + width, (float) texturePosition.y + height);
	model[3].texCoords = sf::Vector2f((float) texturePosition.x, (float) texturePosition.y + height);
}
void Player::updateTexture() {
	int* facing = angleToCardinals(this->getAngle());
	if (facing[2] == 1) {
		texturePosition.y = texHeight * 1;
	}
	else if (facing[3] == 1) {
		texturePosition.y = 0;
	}
	else if (facing[0] == 1) {
		texturePosition.y = texHeight * 3;
	}
	else{
		texturePosition.y = texHeight * 2;
	}
	texturePosition.x = (texturePosition.x + texWidth) % (frameNumbers[texturePosition.y / texHeight] * texWidth);
	setTexturePosition(texturePosition);
}
