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
	Interactable(sf::Vector2f _position, float hitboxRadius, sf::Vector2f hitboxDisplacement = sf::Vector2f(0.f, 0.f), bool visibleHitbox = false);
	Interactable(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, sf::Vector2f hitboxDisplacement = sf::Vector2f(0.f, 0.f), bool visibleHitbox = false);
	Interactable();
	Hitbox* getHitbox() const;
	void importTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo);
	void setTextureCoords(sf::Vector2i texCoords);
	void setTexturePosition(sf::Vector2i texPos);
	sf::Vector2i getTexturePosition();
	sf::Vector2i getTextureDimensions();
	std::vector<int>* getFrameNumbers();
	sf::Vertex* getModel();
	void setModel(sf::Vertex* _model, int _modelSize);
	sf::Texture* getTexture();
	int getID();
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
	int modelSize;
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int id;
};

