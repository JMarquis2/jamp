#pragma once
#include "Unit.h"
#include <SFML/Graphics.hpp>
#include <string>
class Player : public Unit
{
private:
	//this texture errors for some reason in initialization
	//might end up using a resource manager for textures, anyway. So no static texture class member.
	sf::Texture* playerSheet;
	sf::CircleShape tmodel;
	sf::VertexArray vertices;
	sf::Color color;
	float width = 100.f;
	float height = 100.f;
	sf::Vector2i texturePosition;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	~Player();
	Player();
	Player(sf::Vector2f position);
	void setTexture(sf::Texture* tex, sf::Vector2i texPos);
	
};

