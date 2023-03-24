#pragma once
#include "Obstacle.h"
class Wall : public Obstacle
{
private:
	//sf::Texture* wallTexture;
	//sf::Vertex* model;
	//int texWidth;
	//int texHeight;
	//std::vector<int> frameNumbers;
	//sf::Vector2i texturePosition;

	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	~Wall();
	Wall();
	Wall(sf::Vector2f _position, float width, float height);
	/*
	void setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos);
	void setTexturePosition(sf::Vector2i texPos);
	void updateTexture();
	*/
};

