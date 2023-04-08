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
	//this assumes that the texture only has one animation, may need to be modified later.
	sf::Vector2i dimensions = getTextureDimensions();
	int newX = (getTexturePosition().x + dimensions.x) % (getFrameNumbers()->at(0) * dimensions.x);
	setTexturePosition(sf::Vector2i(newX, getTexturePosition().y));
}
void Obstacle::setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo, sf::Vector2i texPos) {
	//sets the texture of the obstacle, and makes it repeatable
	Interactable::importTexture(textureInfo);
	sf::Vector2i texDimensions = getTextureDimensions();

	int columns = dimensions.y / texDimensions.y;
	if (dimensions.y % texDimensions.y != 0)
		columns += 1;
	int rows = dimensions.x / texDimensions.x;
	if (dimensions.x % texDimensions.x != 0)
		rows += 1;
	sf::Vertex* model = new sf::Vertex[rows * columns * 4];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			model[4 * ((i * columns) + j)].position = sf::Vector2f(i * texDimensions.x, j * texDimensions.y);
			model[4 * ((i * columns) + j) + 1].position = sf::Vector2f((i + 1) * texDimensions.x, j * texDimensions.y);
			model[4 * ((i * columns) + j) + 2].position = sf::Vector2f((i + 1) * texDimensions.x, (j + 1) * texDimensions.y);
			model[4 * ((i * columns) + j) + 3].position = sf::Vector2f(i * texDimensions.x, (j + 1) * texDimensions.y);

			model[4 * ((i * columns) + j)].texCoords = sf::Vector2f(0.f, 0.f);
			model[4 * ((i * columns) + j) + 1].texCoords = sf::Vector2f(texDimensions.x, 0.f);
			model[4 * ((i * columns) + j) + 2].texCoords = sf::Vector2f(texDimensions.x, texDimensions.y);
			model[4 * ((i * columns) + j) + 3].texCoords = sf::Vector2f(0.f, texDimensions.y);
		}
	}
	setTextureModel(model, rows * columns * 4);
	
	getTexture()->setRepeated(true);
}