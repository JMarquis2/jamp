#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <list>
#include "collision.h"
#include <utility>
#include <iterator>
#include "moves.h"
#include "Entity.h"
#include "Interactable.h"
#include "Hitbox.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(750, 600), "JAMP, Come in!");
    sf::View view = window.getDefaultView();
    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currTime;
    sf::CircleShape* shape = new sf::CircleShape(25.f);
    sf::RectangleShape wall(sf::Vector2f(100.0f, 20.0f));
    sf::RectangleShape quitZone(sf::Vector2f(50.0f, 50.0f));
    quitZone.setPosition(700, 550);
    quitZone.setFillColor(sf::Color::Red);
    wall.setPosition(100, 500);
    shape->setFillColor(sf::Color::Green);
    sf::RectangleShape wall2(sf::Vector2f(100.0f, 20.0f));
    sf::CircleShape shape2(65.0f);
    shape2.setPosition(400, 400);
    shape2.setFillColor(sf::Color::Cyan);
    wall2.setPosition(250, 150);
    wall2.setFillColor(sf::Color::Blue);
    wall.setFillColor(sf::Color::Black);
    
    sf::Texture* devil = new sf::Texture();
    devil->loadFromFile("devil.png");

    Player dude(sf::Vector2f(500.f, 100.f));

    dude.setTexture(devil, sf::Vector2i(0, 0));

    Player& dudeRef = dude;
    bool menuOpen = false;
    //can't make this an unordered set yet, but is more efficient. Need a hash function for pair of pointers.
    //std::unordered_set<std::pair<sf::CircleShape*, int*>> independents;
    std::list<std::pair<sf::CircleShape*, float*>> independents;
    std::list<std::list<std::pair<sf::CircleShape*, float*>>::iterator> deleteReady;
    std::list<sf::Transformable*> obstacles;
    obstacles.push_back(&wall);

    int* direction{ new int[4]{ 0, 0, 0, 0 } };
    int* prevDirection{ new int[4]{0, 0, 0, 0} };
    //up, down, left, right
    float speed = 500.f;
    while (window.isOpen())
    {
        sf::Event event;
        if (menuOpen) {
            for (int i = 0; i < 4; i++)
                direction[i] = 0;
            currTime = clock.getElapsedTime();
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        menuOpen = false;
                        prevTime = currTime;
                    }
                }
            }
            window.display();
        }
        else {
            if (direction[0] + direction[1] + direction[2] + direction[3] >= 0.0001f) {
                for (int i = 0; i < 4; i++)
                    prevDirection[i] = direction[i];
            }
            view.setCenter(shape->getPosition());
            currTime = clock.getElapsedTime();
            sf::Time elapsed = currTime - prevTime;
            prevTime = currTime;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        menuOpen = true;
                    }
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
                    if (!menuOpen) {
                        if (event.key.code == sf::Keyboard::Q)
                            speed *= 1.2f;
                        if (event.key.code == sf::Keyboard::W)
                            speed /= 1.2f;
                        if (event.key.code == sf::Keyboard::Space) {
                            float* ballisticInfo = new float[5];
                            if (direction[0] + direction[1] + direction[2] + direction[3] <= 0.0001f) {
                                for (int i = 0; i < 4; i++)
                                    ballisticInfo[i] = prevDirection[i];
                            }
                            else {
                                for (int i = 0; i < 4; i++) {
                                    ballisticInfo[i] = direction[i];
                                }
                            }
                            ballisticInfo[4] = speed;
                            sf::CircleShape* shot = new sf::CircleShape(15.0f);
                            sf::Vector2f shotPos = shape->getPosition();
                            shotPos.x += 15.0f;
                            shotPos.y += 15.0f;
                            shot->setPosition(shotPos);
                            shot->setFillColor(sf::Color::Magenta);
                            independents.push_back(std::make_pair(shot, ballisticInfo));
                        }
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
            if (speed < 0)
                speed = 0;
            window.clear(sf::Color::White);
            for (auto it = independents.begin(); it != independents.end(); it++) {
                bool collided = movesWithCollision(it->first, it->second, &elapsed, &obstacles, &window);
                if (collided) {
                    deleteReady.push_back(it);
                }
                /*
                sf::Vector2f curPos = it->first->getPosition();
                sf::Vector2f nextPos = it->first->getPosition();

                float xdiff = (it->second[3] - it->second[2]) * it->second[4] * elapsed.asSeconds();
                float ydiff = (it->second[1] - it->second[0]) * it->second[4] * elapsed.asSeconds();

                if (abs(xdiff) >= 0.0001 && abs(ydiff) >= 0.0001) {
                    xdiff = xdiff / 1.414f;
                    ydiff = ydiff / 1.414f;
                }
                nextPos.x += xdiff;
                nextPos.y += ydiff;
                it->first->setPosition(nextPos);
                window.draw(*(it->first));
                */
            }
            auto curDelete = deleteReady.begin();
            for (int i = 0; i < deleteReady.size(); i++) {
                delete (*curDelete)->first;
                delete(*curDelete)->second;
                independents.erase(*curDelete);
                curDelete++;
            }
            deleteReady.clear();
            //shape moves
            float* shapeMoveInfo = new float[5];
            for (int i = 0; i < 4; i++) {
                shapeMoveInfo[i] = direction[i];
            }
            shapeMoveInfo[4] = speed;
            movesWithCollision(shape, shapeMoveInfo, &elapsed, &obstacles, &window);
            if (collides(shape, &wall2))
                wall2.setFillColor(sf::Color::Red);
            else
                wall2.setFillColor(sf::Color::Blue);
            if (collides(shape, &shape2))
                shape2.setFillColor(sf::Color::Red);
            else
                shape2.setFillColor(sf::Color::Cyan);
            if (collides(shape, &quitZone))
                window.close();
            window.draw(quitZone);
            window.draw(*shape);
            window.draw(shape2);
            window.draw(wall);
            window.draw(wall2);
            window.draw(dudeRef);
            window.setView(view);
            window.display();
        }
    }

    //heap cleanup
    for (auto it = independents.begin(); it != independents.end(); it++) {
        delete it->first;
        delete [] it->second;
    }
    delete[] direction;
    delete[] prevDirection;
    delete shape;
    delete devil;
    return 0;
}