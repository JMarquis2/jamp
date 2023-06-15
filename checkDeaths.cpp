#include "checkDeaths.h"
void checkDeaths(std::list<Enemy*>* enemies) {
    for (auto it = enemies->begin(); it != enemies->end(); it++) {
        if ((*it)->isDead()) {
            it = enemies->erase(it);
            if (it == enemies->end())
                break;
        }
    }
}