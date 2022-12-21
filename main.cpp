#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "collision.h"
#include <utility>

int main()
{
    sf::RenderWindow window(sf::VideoMode(750, 600), "JAMP, Come in!");
    sf::CircleShape shape(25.f);
    sf::RectangleShape wall(sf::Vector2f(100.0f, 20.0f));
    sf::RectangleShape quitZone(sf::Vector2f(50.0f, 50.0f));
    quitZone.setPosition(700, 550);
    quitZone.setFillColor(sf::Color::Red);
    wall.setPosition(100, 500);
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape wall2(sf::Vector2f(100.0f, 20.0f));
    sf::CircleShape shape2(65.0f);
    shape2.setPosition(400, 400);
    shape2.setFillColor(sf::Color::Cyan);
    wall2.setPosition(250, 150);
    wall2.setFillColor(sf::Color::Blue);
    wall.setFillColor(sf::Color::Black);
    //can't make this an unordered set yet, but is more efficient. Need a hash function for pair of pointers.
    //std::unordered_set<std::pair<sf::CircleShape*, int*>> independents;
    std::vector < std::pair < sf::CircleShape*, float*>> independents;
    int direction[] = { 0, 0, 0, 0 };
    //up, down, left, right
    float speed = 0.3f;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                    direction[1] = 1;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    direction[0] = 1;
                }
                if (event.key.code == sf::Keyboard::Left) {
                    direction[2] = 1;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    direction[3] = 1;
                }
                if (event.key.code == sf::Keyboard::Q) {
                    speed *= 1.2f;
                }
                if (event.key.code == sf::Keyboard::W)
                    speed /= 1.2f;
                if (event.key.code == sf::Keyboard::Space) {
                    float* ballisticInfo = new float[5];
                    for (int i = 0; i < 4; i++) {
                        ballisticInfo[i] = direction[i];
                    }
                    ballisticInfo[4] = speed;
                    sf::CircleShape* shot = new sf::CircleShape(15.0f);
                    sf::Vector2f shotPos = shape.getPosition();
                    shotPos.x += 15.0f;
                    shotPos.y += 15.0f;
                    shot->setPosition(shotPos);
                    shot->setFillColor(sf::Color::Magenta);
                    independents.push_back(std::make_pair(shot, ballisticInfo));
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Down) {
                    direction[1] = 0;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    direction[0] = 0;
                }
                if (event.key.code == sf::Keyboard::Left) {
                    direction[2] = 0;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    direction[3] = 0;
                }
            }
        }
        window.clear(sf::Color::White);
        if (speed < 0.01f)
            speed = 0.01f;
        for (int i = 0; i < independents.size(); i++) {
            sf::Vector2f curPos = independents[i].first->getPosition();
            sf::Vector2f nextPos = independents[i].first->getPosition();

            float xdiff = (independents[i].second[3] - independents[i].second[2]) * speed;
            float ydiff = (independents[i].second[1] - independents[i].second[0]) * speed;

            if (abs(xdiff) >= 0.0001 && abs(ydiff) >= 0.0001) {
                xdiff = xdiff / 1.414f;
                ydiff = ydiff / 1.414f;
            }
            nextPos.x += xdiff;
            nextPos.y += ydiff;
            independents[i].first->setPosition(nextPos);
            window.draw(*(independents[i].first));
        }
        //shape moves
        sf::Vector2f nextPos = shape.getPosition();
        sf::Vector2f curPos = shape.getPosition();
        float xdiff = (direction[3] - direction[2]) * speed;
        float ydiff = (direction[1] - direction[0]) * speed;
        float circleRadius = shape.getRadius();
        if (abs(xdiff) >= 0.0001 && abs(ydiff) >= 0.0001) {
            xdiff = xdiff / 1.414f;
            ydiff = ydiff / 1.414f;
        }
        nextPos.x += xdiff;
        sf::Vector2f circleCenter;
        //circleCenter.x = nextPos.x + circleRadius;
        //circleCenter.y = nextPos.y + circleRadius;
        shape.setPosition(nextPos);
        if (collides(&shape, &wall)) {
            shape.setPosition(curPos);
            nextPos.x -= xdiff;
        }
        else {
            curPos.x = nextPos.x;
        }
        nextPos.y += ydiff;
        shape.setPosition(nextPos);
        if (collides(&shape, &wall)) {
            shape.setPosition(curPos);
            nextPos.y -= ydiff;
        }
        if (collides(&shape, &wall2))
            wall2.setFillColor(sf::Color::Red);
        else
            wall2.setFillColor(sf::Color::Blue);
        if (collides(&shape, &shape2))
            shape2.setFillColor(sf::Color::Red);
        else
            shape2.setFillColor(sf::Color::Cyan);
        if (collides(&shape, &quitZone))
            window.close();
        shape.setPosition(nextPos);
        window.draw(quitZone);
        window.draw(shape);
        window.draw(shape2);
        window.draw(wall);
        window.draw(wall2);
        window.display();
    }

    return 0;
}