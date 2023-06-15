#pragma once
#include "Player.h"
#include "Attack.h"
#include "Enemy.h"
//checks whether attacks are colliding with obstacles, enemies, or player
void checkCollisions(Player* player, std::list<Attack*>* hits, std::list<Obstacle*>* obstacles, std::list<Enemy*>* enemies, sf::Time elapsed);