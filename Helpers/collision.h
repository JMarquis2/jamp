#pragma once
#include <SFML/Graphics.hpp>
#include "../Classes/Interactable.h"
bool checkAngledRects(std::vector<sf::Vector2f>& first, std::vector<sf::Vector2f>& second);
bool collidesRectCirc(sf::RectangleShape* rect, sf::CircleShape* circ);
bool collidesRectRect(sf::RectangleShape* first, sf::RectangleShape* second);
bool collidesCircCirc(sf::CircleShape* first, sf::CircleShape* second);
bool collides(sf::Shape* first, sf::Shape* second);
bool collides(Interactable* first, Interactable* second);