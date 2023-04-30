#pragma once
#include <SFML/Graphics.hpp>
class Terrain : public sf::Transformable, public sf::Drawable
{
public:
	~Terrain();
	Terrain();
	Terrain(sf::Vector2f position, int width, int height);
	void importTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo);
	void setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo);
private:
	//grassVarieties is a placeholder, for testing out grass textures. In the future, I'll have a data structure which keeps track of different types of backgrounds.
	int grassVarieties;
	sf::Vector2i dimensions;
	sf::Vector2i texDimensions;
	sf::Texture* textureSheet;
	//std::vector<std::vector<int>> tilemap;
	int* tilemap;
	sf::Vertex* model;
	int modelSize;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

