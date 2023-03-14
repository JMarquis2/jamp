#include <SFML/Graphics.hpp>
#include <list>
#include "Entity.h"
int* angleToCardinals(float angle);
float cardinalsToAngle(int* cardinals);

bool movesWithCollision(sf::Shape* mover, float* moveInfo, sf::Time* elapsed, std::list<sf::Transformable*>* obstacles, sf::RenderWindow* window);
bool movesWithCollision(sf::Sprite* mover, float* moveInfo, sf::Time* elapsed, std::list<sf::Transformable*>* obstacles, sf::RenderWindow* window);
bool movesWithCollision(Entity* mover, float angle, float dist, sf::Time* elapsed, std::list<Interactable*>* obstacles, sf::RenderWindow* window);