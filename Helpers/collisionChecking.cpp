#include "collisionChecking.h"
#include "collision.h"
void checkCollisions(Player* player, std::list<Attack*>* hits, std::list<Obstacle*>* obstacles, std::list<Enemy*>* enemies, sf::Time elapsed) {
    //collisions between hits and enemies that can be hit
    for (auto hitsIter = hits->begin(); hitsIter != hits->end(); hitsIter++) {
        bool exists = true;
        for (auto enemiesIter = enemies->begin(); enemiesIter != enemies->end(); enemiesIter++) {
            if (collides(*hitsIter, *enemiesIter)) {
                if (!(*hitsIter)->hits(*enemiesIter)) {
                    delete (*hitsIter);
                    hitsIter = hits->erase(hitsIter);
                    if (hitsIter == hits->end()) {
                        exists = false;
                    }
                    break;
                }
            }
        }
        if (!exists)
            break;
    }

    //check collisions between player and enemies
    for (auto it = enemies->begin(); it != enemies->end(); it++) {
        if (collides(player, *it)) {
            player->takeDamage((*it)->getCollisionDPS() * elapsed.asSeconds());
        }
    }
}