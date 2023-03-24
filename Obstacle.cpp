#include "Obstacle.h"
Obstacle::Obstacle() : Interactable() {
}
Obstacle::~Obstacle() {

}
Obstacle::Obstacle(sf::Vector2f _position, float radius) : Interactable(_position, radius) {

}
Obstacle::Obstacle(sf::Vector2f _position, float width, float height) : Interactable(_position, width, height){

}
void Obstacle::updateTexture() {
	sf::Vector2i dimensions = getTextureDimensions();
	int newX = (getTexturePosition().x + dimensions.x) % (getFrameNumbers()->at(0) * dimensions.x);
	setTexturePosition(sf::Vector2i(newX, getTexturePosition().y));
}
void Obstacle::setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos) {
	Interactable::setTexture(textureInfo, texPos);
	getTexture()->setRepeated(true);
}