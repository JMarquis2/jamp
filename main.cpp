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
#include "Wall.h"
#include "Terrain.h"

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

    //currently set to 1/12 of a second. Customizable...
    sf::Time spriteUpdateTimer = sf::seconds(0.0833333f);
    sf::Time spriteUpdateElapsed;
    
    // shapes to test with 
    
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

    //first, add all texture names to vector. Eventually, this could even be read from a file.
    std::vector<std::string> textureNames;
    textureNames.push_back("player_knight");
    textureNames.push_back("Hedge");
    textureNames.push_back("ground");
    textureNames.push_back("grass");
    textureNames.push_back("cobble");

    //then, construct texturemanager using vector.
    TextureManager texmachine(textureNames);

    //if you want to add another texture, you could also call importTexture(name);

    Player testDude(sf::Vector2f(0.f, 0.f));
    testDude.setTexture(texmachine.getTextureInfo("player_knight"), sf::Vector2i(0, 0));

    Player dude(sf::Vector2f(0.f, 0.f));
    dude.setTexture(texmachine.getTextureInfo("player_knight"), sf::Vector2i(0, 0));

    Wall hedge(sf::Vector2f(500.f, 500.f), 200, 30);
    hedge.setTexture(texmachine.getTextureInfo("Hedge"), sf::Vector2i(0, 0));

    Terrain grassyTerrain(sf::Vector2f(0.f, 0.f), 1000, 1000);
    grassyTerrain.setTexture(texmachine.getTextureInfo("grass"));

    Terrain cobbleTerrain(sf::Vector2f(1000.f, 0.f), 1000, 1000);
    cobbleTerrain.setTexture(texmachine.getTextureInfo("cobble"));


    sf::Sprite testgrass1;
    sf::Sprite testgrass2;
    sf::Sprite testgrass3;
    sf::Sprite testgrass4;
    sf::Sprite testgrass5;
    testgrass1.setTexture(*(texmachine.getTextureInfo("ground").second));
    testgrass1.setPosition(sf::Vector2f(1000.f, 1000.f));
    
    int x_pos = 0;
    int y_pos = 0;

    bool menuOpen = false;
    //can't make this an unordered set yet, but is more efficient. Need a hash function for pair of pointers.
    //std::unordered_set<std::pair<sf::CircleShape*, int*>> independents;
    std::list<std::pair<sf::CircleShape*, float*>> independents;
    std::list<std::list<std::pair<sf::CircleShape*, float*>>::iterator> deleteReady;
    std::list<Obstacle*> obstacles;
    obstacles.push_back(&hedge);

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
                        dude.setTextureCoords(sf::Vector2i(x_pos, y_pos));
                    }
                    if (event.key.code == sf::Keyboard::Up) {
                        direction[0] = 1;
                        y_pos = 300;
                        x_pos = (x_pos + 100) % 300;
                        dude.setTextureCoords(sf::Vector2i(x_pos, y_pos));
                    }
                    if (event.key.code == sf::Keyboard::Left) {
                        direction[2] = 1;
                        y_pos = 100;
                        x_pos = (x_pos + 100) % 300;
                        dude.setTextureCoords(sf::Vector2i(x_pos, y_pos));
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        direction[3] = 1;
                        y_pos = 0;
                        x_pos = (x_pos + 100) % 300;
                        dude.setTextureCoords(sf::Vector2i(x_pos, y_pos));
                    }
                    if (!menuOpen) {
                        if (event.key.code == sf::Keyboard::Q)
                            speed *= 1.5f;
                        if (event.key.code == sf::Keyboard::W)
                            speed /= 1.5f;
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

            //iterate through game logic

            //clear the window, prepare to draw sprites
            window.clear(sf::Color::White);

            //loop through physics stuff...
            movesWithCollision(&testDude, cardinalsToAngle(prevDirection), &elapsed, &obstacles, &window);
            
            //loop to update sprite animations -- runs 12 times per second
            if (spriteUpdateElapsed >= spriteUpdateTimer) {
                spriteUpdateElapsed -= spriteUpdateTimer;
                /*
                loop through every animated object, run "update sprite" function
                */
                testDude.updateTexture();
            }

            //std::cout << "testDude hitbox pos: " << testDude.getHitbox()->getHitShape()->getPosition().x << " ";
            //std::cout << testDude.getHitbox()->getHitShape()->getPosition().y << std::endl;

            //draw our drawable objects
            window.draw(grassyTerrain);
            window.draw(cobbleTerrain);
            window.draw(quitZone);
            window.draw(shape2);
            window.draw(wall);
            window.draw(wall2);
            //this isnt working for some reason?? nevermind im dumb
            window.draw(hedge);
            window.draw(testgrass1);
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
    return 0;
}