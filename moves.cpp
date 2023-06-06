#include "moves.h"
#include "collision.h"
#include <SFML/Graphics.hpp>
#include <iterator>
#include "Entity.h"
#include <math.h>
//moveInfo is a 5-length array which contains first the directions being traveled, then the speed.
#define PI 3.14159265f

std::vector<int> angleToCardinals(float angle) {
    std::vector<int> directionArray(4, 0);
    float x = round(cos(angle * PI / 180.0f));
    float y = round(sin(angle * PI / 180.0f));
    if (abs(x - 1.f) < 0.0001)
        directionArray[3] = 1;
    if (abs(x + 1.f) < 0.0001)
        directionArray[2] = 1;
    if (abs(y - 1.f) < 0.0001)
        directionArray[0] = 1;
    if (abs(y + 1.f) < 0.0001)
        directionArray[1] = 1;
    return directionArray;
}
float cardinalsToAngle(int* cardinals) {
    int xdiff = cardinals[3] - cardinals[2];
    int ydiff = cardinals[0] - cardinals[1];
    float angle = 0.f;

    if (ydiff >= 0) {
        angle = atan2((float)ydiff, (float)xdiff);
    }
    else
        angle = 2 * PI - (-1.f * atan2((float)ydiff, (float)xdiff));
    return (angle * 180.f / PI);
}


float entityToEntityAngle(sf::Vector2f entityPos, sf::Vector2f entity2Pos) {
    sf::Vector2f distance = entityPos - entity2Pos;
    float angle = 0.f;
    if (distance.y >= 0) {
        angle = atan2((float)distance.y, -1*(float)distance.x);
    }
    else
        angle = 2 * PI - (-1.f * atan2((float)distance.y, -1 * (float)distance.x));
    return (angle * 180.f / PI);


    

}
/*
bool movesWithCollision(sf::Shape* mover, float* moveInfo, sf::Time* elapsed, std::list<Obstacle*>* obstacles, sf::RenderWindow* window){
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
bool movesWithCollision(sf::Sprite* mover, float* moveInfo, sf::Time* elapsed, std::list<Obstacle*>* obstacles, sf::RenderWindow* window) {
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
*/
bool movesWithCollision(Entity* mover, float angle, sf::Time* elapsed, std::list<Obstacle*>* obstacles, sf::RenderWindow* window) {
    if (mover->getIdle()) {
        return false;
    }
    sf::Vector2f curPos = mover->getPosition();
    sf::Vector2f nextPos = mover->getPosition();
    bool collided = false;
    float dist = elapsed->asSeconds() * mover->getSpeed();

    float xdiff = cos(angle * PI / 180.f) * dist;
    float ydiff = -1 * sin(angle * PI / 180.f) * dist;

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
