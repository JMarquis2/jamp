#include "Wall.h"
#include "moves.h"
#include <iostream>

Wall::~Wall() {
	//delete model;
}
Wall::Wall() : Obstacle() {
	dimensions.x = 0.f;
	dimensions.y = 0.f;
	//wallTexture = nullptr;
	//model = nullptr;
}
Wall::Wall(sf::Vector2f _position, float width, float height) : Obstacle(_position, width, height){
	dimensions.x = width;
	dimensions.y = height;
	/*
	model = new sf::Vertex[4];
	model[0].position = sf::Vector2f(0.f, 0.f);
	model[1].position = sf::Vector2f(width, 0.f);
	model[2].position = sf::Vector2f(width, height);
	model[3].position = sf::Vector2f(0.f, height);
	wallTexture = nullptr;
	*/
}/*
void Wall::setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos) {
	wallTexture = textureInfo.second;
	texWidth = textureInfo.first->at(0);
	texHeight = textureInfo.first->at(1);
	for (int i = 0; i < textureInfo.first->at(2); i++) {
		frameNumbers.push_back(textureInfo.first->at(i + 3));
	}
	setTexturePosition(texPos);
	wallTexture->setRepeated(true);
}
void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (wallTexture) {
		states.texture = wallTexture;
		states.transform = this->getTransform();
		target.draw(model, 4, sf::Quads, states);
		//target.draw(vertices, states);
	}
	else {
		std::cout << "error: no texture set for wall class" << std::endl;
	}
}
void Wall::setTexturePosition(sf::Vector2i texPos) {
	texturePosition.x = texPos.x;
	texturePosition.y = texPos.y;
	model[0].texCoords = sf::Vector2f((float)texturePosition.x, (float)texturePosition.y);
	model[1].texCoords = sf::Vector2f((float)texturePosition.x + width, (float)texturePosition.y);
	model[2].texCoords = sf::Vector2f((float)texturePosition.x + width, (float)texturePosition.y + height);
	model[3].texCoords = sf::Vector2f((float)texturePosition.x, (float)texturePosition.y + height);
}
void Wall::updateTexture() {
	texturePosition.x = (texturePosition.x + texWidth) % (frameNumbers[texturePosition.y / texHeight] * texWidth);
	setTexturePosition(texturePosition);
}
*/