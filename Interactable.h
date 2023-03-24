#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
class Interactable : public sf::Transformable, public sf::Drawable
{
public:
	//actual dimensions
	sf::Vector2i dimensions;

	bool collidesWith(Interactable* other);
	~Interactable();
	//one for circular hitbox, one for rectangular
	Interactable(sf::Vector2f _position, float hitboxRadius, bool visibleHitbox = false);
	Interactable(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, bool visibleHitbox = false);
	Interactable();
	Hitbox* getHitbox() const;
	void setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos);
	void setTexturePosition(sf::Vector2i texPos);
	sf::Vector2i getTexturePosition();
	sf::Vector2i getTextureDimensions();
	std::vector<int>* getFrameNumbers();

	sf::Texture* getTexture();
private:
	//hitbox stuff?
	Hitbox* hitbox;
	sf::Vector2f position;

	//texture information
	sf::Texture* textureSheet;
	int texWidth;
	int texHeight;
	std::vector<int> frameNumbers;
	sf::Vector2i texturePosition;
	sf::Vertex* model;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

