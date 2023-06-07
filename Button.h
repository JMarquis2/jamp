#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Button : public sf::Transformable, public sf::Drawable
{
private:
	int target;
	bool isPressed;
	bool clickable;
	std::string description;
	sf::Vector2f dimensions;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int Poll();
	Button(int _target, std::string _description, sf::Vector2f _position, sf::Vector2f _dimensions);
	int Click(sf::Vector2f mousePosition);
};

