#pragma once
#include "Unit.h"
#include <SFML/Graphics.hpp>
#include <string>
class Player : public Unit
{
private:
	//this texture errors for some reason in initialization
	//might end up using a resource manager for textures, anyway. So no static texture class member.
	static sf::Texture playerSheet;
	static sf::Sprite playerImage;
	sf::CircleShape tmodel;
	sf::Color color;
public:
	~Player();
	Player();
	Player(sf::Vector2f position);
	static void loadSpriteFromFile(std::string filename);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

