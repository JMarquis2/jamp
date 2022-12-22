#include "moves.h"
#include "collision.h"
#include <SFML/Graphics.hpp>
#include <iterator>
//moveInfo is a 5-length array which contains first the directions being traveled, then the speed.
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