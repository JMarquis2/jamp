#include "moves.h"
#include "collision.h"
#include <SFML/Graphics.hpp>
#include <iterator>
#include "Entity.h"
#include <math.h>
//moveInfo is a 5-length array which contains first the directions being traveled, then the speed.
int* angleToNearestCardinals(float angle) {
    int directionArray[] = { 0, 0, 0, 0 };
    directionArray[((int)round(angle) / 90) % 4] = 1;
}
float cardinalsToAngle(int* cardinals) {
    if (cardinals[0] == 1)
        return 0.f;
    if (cardinals[1] == 1)
        return 90.f;
    if (cardinals[2] == 1)
        return 180.f;
    else
        return 270.f;
}

bool movesWithCollision(sf::Shape* mover, float* moveInfo, sf::Time* elapsed, std::list<sf::Transformable*>* obstacles, sf::RenderWindow* window){
	float curX = mover->getPosition().x;
	float curY = mover->getPosition().y;
    sf::Vector2f curPos = mover->getPosition();
    sf::Vector2f nextPos = mover->getPosition();
    bool collided = false;

    float xdiff = (moveInfo[3] - moveInfo[2]) * moveInfo[4] * elapsed->asSeconds();
    float ydiff = (moveInfo[1] - moveInfo[0]) * moveInfo[4] * elapsed->asSeconds();

    if (abs(xdiff) >= 0.0001 && abs(ydiff) >= 0.0001) {
        xdiff = xdiff / 1.414f;
        ydiff = ydiff / 1.414f;
    }
    nextPos.x += xdiff;
    mover->setPosition(nextPos);
    for (auto it = obstacles->begin(); it != obstacles->end(); it++) {
        if (collides(mover, *it)) {
            mover->setPosition(curPos);
            nextPos.x -= xdiff;
            collided = true;
            break;
        }
        if (std::next(it) == obstacles->end()) {
            curPos.x = nextPos.x;
        }
    }
    nextPos.y += ydiff;
    mover->setPosition(nextPos);
    for (auto it = obstacles->begin(); it != obstacles->end(); it++) {
        if (collides(mover, *it)) {
            mover->setPosition(curPos);
            collided = true;
            nextPos.y -= ydiff;
            break;
        }
    }
    window->draw(*mover);
    return collided;
}
bool movesWithCollision(sf::Sprite* mover, float* moveInfo, sf::Time* elapsed, std::list<sf::Transformable*>* obstacles, sf::RenderWindow* window) {
    float curX = mover->getPosition().x;
    float curY = mover->getPosition().y;
    sf::Vector2f curPos = mover->getPosition();
    sf::Vector2f nextPos = mover->getPosition();
    bool collided = false;

    float xdiff = (moveInfo[3] - moveInfo[2]) * moveInfo[4] * elapsed->asSeconds();
    float ydiff = (moveInfo[1] - moveInfo[0]) * moveInfo[4] * elapsed->asSeconds();

    if (abs(xdiff) >= 0.0001 && abs(ydiff) >= 0.0001) {
        xdiff = xdiff / 1.414f;
        ydiff = ydiff / 1.414f;
    }
    nextPos.x += xdiff;
    mover->setPosition(nextPos);
    for (auto it = obstacles->begin(); it != obstacles->end(); it++) {
        if (collides(mover, *it)) {
            mover->setPosition(curPos);
            collided = true;
            nextPos.x -= xdiff;
            break;
        }
        if (std::next(it) == obstacles->end()) {
            curPos.x = nextPos.x;
        }
    }
    nextPos.y += ydiff;
    mover->setPosition(nextPos);
    for (auto it = obstacles->begin(); it != obstacles->end(); it++) {
        if (collides(mover, *it)) {
            mover->setPosition(curPos);
            collided = true;
            nextPos.y -= ydiff;
            break;
        }
    }
    window->draw(*mover);
    return collided;
}
bool movesWithCollision(Entity* mover, float angle, float dist, sf::Time* elapsed, std::list<Interactable*>* obstacles, sf::RenderWindow* window) {
    sf::Vector2f curPos = mover->getPosition();
    sf::Vector2f nextPos = mover->getPosition();
    bool collided = false;

    float xdiff = cos(angle) * dist * elapsed->asSeconds();
    float ydiff = sin(angle) * dist * elapsed->asSeconds();

    nextPos.x += xdiff;
    mover->moveToPosition(nextPos);
    for (auto it = obstacles->begin(); it != obstacles->end(); it++) {
        if (collides(mover, *it)) {
            mover->moveToPosition(curPos);
            collided = true;
            nextPos.x -= xdiff;
            break;
        }
        if (std::next(it) == obstacles->end()) {
            curPos.x = nextPos.x;
        }
    }
    nextPos.y += ydiff;
    mover->moveToPosition(nextPos);
    for (auto it = obstacles->begin(); it != obstacles->end(); it++) {
        if (collides(mover, *it)) {
            mover->moveToPosition(curPos);
            collided = true;
            nextPos.y -= ydiff;
            break;
        }
    }
    window->draw(*mover);
    return collided;
}