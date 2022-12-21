#pragma once
#include <SFML/Graphics.hpp>
bool collidesRectCirc(sf::RectangleShape* rect, sf::CircleShape* circ);
bool collidesRectSprite(sf::RectangleShape* rect, sf::Sprite* sprite);
bool collidesRectRect(sf::RectangleShape* first, sf::RectangleShape* second);
bool collidesCircSprite(sf::CircleShape* circ, sf::Sprite* sprite);
bool collidesCircCirc(sf::CircleShape* first, sf::CircleShape* second);
bool collidesSpriteSprite(sf::Sprite* first, sf::Sprite* second);
bool collides(sf::Transformable* first, sf::Transformable* second);