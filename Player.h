#pragma once
#include "Unit.h"
#include <SFML/Graphics.hpp>
#include <string>
class Player : public Unit
{
private:
	//need to put textures and drawing into a base class.
	//sf::Texture* playerSheet;
	//sf::Vertex* model;
	sf::Color color;
	/*
	int texWidth;
	int texHeight;
	std::vector<int> frameNumbers;
	sf::Vector2i texturePosition;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	*/
public:
	~Player();
	Player();
	Player(sf::Vector2f position);
	/*
	void setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos);
	void setTexturePosition(sf::Vector2i texPos);
	void updateTexture();
	*/
};

