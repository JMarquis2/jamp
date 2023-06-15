#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
#include "Obstacle.h"
#include "Player.h"
//up down left right

std::vector<int> angleToCardinals(float angle);
float cardinalsToAngle(int* cardinals);
float entityToEntityAngle(sf::Vector2f entity, sf::Vector2f Player);
bool movesWithCollision(Entity* mover, float angle, sf::Time* elapsed, std::list<Obstacle*>* obstacles);
void moveEntities(Player* player, std::list<Entity*>* entities, sf::Time elapsed, std::list<Obstacle*>* obstacles);