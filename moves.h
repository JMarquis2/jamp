#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
#include "Obstacle.h"
//up down left right

std::vector<int> angleToCardinals(float angle);
float cardinalsToAngle(int* cardinals);
float entityToEntityAngle(sf::Vector2f entity, sf::Vector2f Player);

//bool movesWithCollision(sf::Shape* mover, float* moveInfo, sf::Time* elapsed, std::list<Obstacle*>* obstacles, sf::RenderWindow* window);
//bool movesWithCollision(sf::Sprite* mover, float* moveInfo, sf::Time* elapsed, std::list<Obstacle*>* obstacles, sf::RenderWindow* window);
bool movesWithCollision(Entity* mover, float angle, sf::Time* elapsed, std::list<Obstacle*>* obstacles);