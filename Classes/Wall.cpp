#include "Wall.h"
#include "../Helpers/moves.h"
#include <iostream>

Wall::~Wall() {
}
Wall::Wall() : Obstacle() {
	dimensions.x = 0.f;
	dimensions.y = 0.f;
}
Wall::Wall(sf::Vector2f _position, float width, float height) : Obstacle(_position, width, height) {
	dimensions.x = width;
	dimensions.y = height;
}