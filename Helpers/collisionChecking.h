#pragma once
#include "../Classes/Player.h"
#include "../Classes/Attack.h"
#include "../Classes/Enemy.h"
//checks whether attacks are colliding with obstacles, enemies, or player
void checkCollisions(Player* player, std::list<Attack*>* hits, std::list<Obstacle*>* obstacles, std::list<Enemy*>* enemies, sf::Time elapsed);