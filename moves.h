#include <SFML/Graphics.hpp>
#include <list>
bool movesWithCollision(sf::Shape* mover, float* moveInfo, sf::Time* elapsed, std::list<sf::Transformable*>* obstacles, sf::RenderWindow* window);
bool movesWithCollision(sf::Sprite* mover, float* moveInfo, sf::Time* elapsed, std::list<sf::Transformable*>* obstacles, sf::RenderWindow* window);