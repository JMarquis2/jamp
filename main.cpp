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
#include "TextureManager.h"
#include <iostream>

int main()
{
    // sets up windows
    sf::RenderWindow window(sf::VideoMode(750, 600), "JAMP, Come in!");
    sf::View view = window.getDefaultView();
    
    // sets up clock 
    sf::Clock clock;
    sf::Time prevTime = clock.getElapsedTime();
    sf::Time currTime;
    sf::Time elapsed;

    sf::Time spriteUpdateTimer = sf::seconds(0.0833333f);
    sf::Time spriteUpdateElapsed;
    
    // shapes to test with 
    sf::CircleShape* shape = new sf::CircleShape(50.f);
    shape->setFillColor(sf::Color::Green);
    
    sf::CircleShape shape2(65.0f);
    shape2.setPosition(400, 400);
    shape2.setFillColor(sf::Color::Cyan);
   
    
    sf::RectangleShape wall(sf::Vector2f(100.0f, 20.0f));
    wall.setPosition(100, 500);
    wall.setFillColor(sf::Color::Black);

    sf::RectangleShape wall2(sf::Vector2f(100.0f, 20.0f));
    wall2.setPosition(250, 150);
    wall2.setFillColor(sf::Color::Blue);


    sf::RectangleShape quitZone(sf::Vector2f(50.0f, 50.0f));
    quitZone.setPosition(700, 550);
    quitZone.setFillColor(sf::Color::Red);

    //example:use texturemanager

    //first, add all texture names to vector.
    std::vector<std::string> textureNames;
    textureNames.push_back("player_knight");

    //then, construct texturemanager using vector.
    TextureManager texmachine(textureNames);

    //if you want to add another texture, you could also call importTexture(name);

    Player testDude(sf::Vector2f(100.f, 100.f));
    testDude.setTexture(texmachine.getTextureInfo("player_knight"), sf::Vector2i(0, 0));

    Player dude(sf::Vector2f(0.f, 0.f));
    dude.setTexture(texmachine.getTextureInfo("player_knight"), sf::Vector2i(0, 0));
    
    int x_pos = 0;
    int y_pos = 0;

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
    testDude.setSpeed(speed);
    while (window.isOpen())
    {
        sf::Event event;
        //game is paused
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
        //the game is playing
        else {
            //set previous directions to last looped directions if new inputs
            if (direction[0] + direction[1] + direction[2] + direction[3] >= 0.0001f) {
                for (int i = 0; i < 4; i++)
                    prevDirection[i] = direction[i];
                testDude.setIdle(false);
            }
            else {
                testDude.setIdle(true);
            }
            testDude.setAngle(cardinalsToAngle(prevDirection));
            //update view
            view.setCenter(testDude.getPosition());

            //update time
            currTime = clock.getElapsedTime();
            elapsed = currTime - prevTime;
            prevTime = currTime;
            spriteUpdateElapsed += elapsed;

            //check for button presses
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
                        y_pos = 200;
                        x_pos = (x_pos + 100) % 300;
                        std::cout << x_pos << std::endl;
                        dude.setTexturePosition(sf::Vector2i(x_pos, y_pos));
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        direction[0] = 1;
                        y_pos = 300;
                        x_pos = (x_pos + 100) % 300;
                        std::cout << x_pos << std::endl;
                        dude.setTexturePosition(sf::Vector2i(x_pos, y_pos));
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        direction[2] = 1;
                        y_pos = 100;
                        x_pos = (x_pos + 100) % 300;
                        std::cout << x_pos << std::endl;
                        dude.setTexturePosition(sf::Vector2i(x_pos, y_pos));
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        direction[3] = 1;
                        y_pos = 0;
                        x_pos = (x_pos + 100) % 300;
                        std::cout << x_pos << std::endl;
                        dude.setTexturePosition(sf::Vector2i(x_pos, y_pos));
                      

                    }
                    if (!menuOpen) {
                        if (event.key.code == sf::Keyboard::Q)
                            speed *= 1.5f;
                        if (event.key.code == sf::Keyboard::W)
                            speed /= 1.5f;
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

            //clear the window, prepare to draw sprites
            window.clear(sf::Color::White);


            //temporary iteration through "bullets" shot with space bar
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

            //temporary iteration to delete "bullets" that collided with walls
            auto curDelete = deleteReady.begin();
            for (int i = 0; i < deleteReady.size(); i++) {
                delete (*curDelete)->first;
                delete(*curDelete)->second;
                independents.erase(*curDelete);
                curDelete++;
            }
            deleteReady.clear();

            //loop through physics stuff...
            movesWithCollision(&testDude, cardinalsToAngle(prevDirection), &elapsed, &obstacles, &window);
            std::cout << testDude.getPosition().x;
            std::cout << " " << testDude.getPosition().y << std::endl;
            //std::cout << cardinalsToAngle(direction) << std::endl;

            //shape moves
            float* shapeMoveInfo = new float[5];
            for (int i = 0; i < 4; i++) {
                shapeMoveInfo[i] = direction[i];
            }
            shapeMoveInfo[4] = speed;
            movesWithCollision(shape, shapeMoveInfo, &elapsed, &obstacles, &window);
            
            //loop to update sprite animations -- runs 12 times per second
            if (spriteUpdateElapsed >= spriteUpdateTimer) {
                spriteUpdateElapsed -= spriteUpdateTimer;
                /*
                loop through every animated object, run "update sprite" function
                */
                testDude.updateTexture();
            }

            //temporary collision checks
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

            //draw our drawable objects
            window.draw(quitZone);
            window.draw(*shape);
            window.draw(shape2);
            window.draw(wall);
            window.draw(wall2);
            //this isnt working for some reason?? nevermind im dumb
            window.draw(dude);
            window.draw(testDude);

            window.setView(view);
            window.display();
        }
    }

    //heap cleanup
    for (auto it = independents.begin(); it != independents.end(); it++) {
        delete it->first;
        delete[] it->second;
    }
    delete[] direction;
    delete[] prevDirection;
    delete shape;
    return 0;
}