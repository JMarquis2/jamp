#include "Obstacle.h"
Obstacle::Obstacle() : Interactable() {
}
Obstacle::~Obstacle() {

}
Obstacle::Obstacle(sf::Vector2f _position, float radius) : Interactable(_position, radius) {

}
Obstacle::Obstacle(sf::Vector2f _position, float width, float height) : Interactable(_position, width, height){

}