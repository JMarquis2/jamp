#pragma once
#include "Interactable.h"
class Obstacle : public Interactable{	
public:
	~Obstacle();
	Obstacle();
	Obstacle(sf::Vector2f _position, float radius);
	Obstacle(sf::Vector2f _position, float width, float height);
	void updateTexture();
	void setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos);
private:

};

