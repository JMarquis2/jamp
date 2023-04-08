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

	int rows = dimensions.y / texDimensions.y;
	if (dimensions.y % texDimensions.y != 0)
		rows += 1;
	int columns = dimensions.x / texDimensions.x;
	if (dimensions.x % texDimensions.x != 0)
		columns += 1;
	sf::Vertex* model = new sf::Vertex[rows * columns * 4];
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			int currRight = (i + 1) * texDimensions.x;
			int texRight = texDimensions.x;
			int currBot = (j + 1) * texDimensions.y;
			int texBot = texDimensions.y;
			if (currRight > dimensions.x) {
				currRight = i * texDimensions.x + dimensions.x % texDimensions.x;
				texRight = dimensions.x % texDimensions.x;
			}
			if (currBot > dimensions.y) {
				currBot = j * texDimensions.y + dimensions.y % texDimensions.y;
				texBot = dimensions.y % texDimensions.y;
			}
			model[4 * ((i * rows) + j)].position = sf::Vector2f(i * texDimensions.x, j * texDimensions.y);
			model[4 * ((i * rows) + j) + 1].position = sf::Vector2f(currRight, j * texDimensions.y);
			model[4 * ((i * rows) + j) + 2].position = sf::Vector2f(currRight, currBot);
			model[4 * ((i * rows) + j) + 3].position = sf::Vector2f(i * texDimensions.x, currBot);

			model[4 * ((i * rows) + j)].texCoords = sf::Vector2f(0.f, 0.f);
			model[4 * ((i * rows) + j) + 1].texCoords = sf::Vector2f(texRight, 0.f);
			model[4 * ((i * rows) + j) + 2].texCoords = sf::Vector2f(texRight, texBot);
			model[4 * ((i * rows) + j) + 3].texCoords = sf::Vector2f(0.f, texBot);

		}
	}
	setTextureModel(model, rows * columns * 4);
}