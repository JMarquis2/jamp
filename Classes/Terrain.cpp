#include "Terrain.h"
#include <time.h>
#include <cstdlib>
Terrain::~Terrain() {
	delete[] model;
}
Terrain::Terrain() {
	this->setPosition(0, 0);
	dimensions.x = 10;
	dimensions.y = 10;
	tilemap = new int[100];
}
Terrain::Terrain(sf::Vector2f position, int width, int height) {
	this->setPosition(position);
	dimensions.x = width;
	dimensions.y = height;
	tilemap = new int[width * height];
}
void Terrain::importTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo) {
	textureSheet = textureInfo.second;
	texDimensions.x = textureInfo.first->at(0);
	texDimensions.y = textureInfo.first->at(1);
	grassVarieties = textureInfo.first->at(2);
}
void Terrain::setTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo) {
	//sets the texture of the obstacle, and makes it repeatable
	Terrain::importTexture(textureInfo);

	int rows = dimensions.y / texDimensions.y;
	if (dimensions.y % texDimensions.y != 0)
		rows += 1;
	int columns = dimensions.x / texDimensions.x;
	if (dimensions.x % texDimensions.x != 0)
		columns += 1;

	srand(time(NULL));
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			tilemap[i * rows + j] = rand() % grassVarieties;
		}
	}

	model = new sf::Vertex[rows * columns * 4];
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			int currRight = (i + 1) * texDimensions.x;
			int texRight = texDimensions.x;
			int currBot = (j + 1) * texDimensions.y;
			int texBot = tilemap[i * rows + j] * texDimensions.y + texDimensions.y;
			if (currRight > dimensions.x) {
				currRight = i * texDimensions.x + dimensions.x % texDimensions.x;
				texRight = dimensions.x % texDimensions.x;
			}
			if (currBot > dimensions.y) {
				currBot = j * texDimensions.y + dimensions.y % texDimensions.y;
				texBot = tilemap[i * rows + j] * texDimensions.y + dimensions.y % texDimensions.y;
			}
			model[4 * ((i * rows) + j)].position = sf::Vector2f(i * texDimensions.x, j * texDimensions.y);
			model[4 * ((i * rows) + j) + 1].position = sf::Vector2f(currRight, j * texDimensions.y);
			model[4 * ((i * rows) + j) + 2].position = sf::Vector2f(currRight, currBot);
			model[4 * ((i * rows) + j) + 3].position = sf::Vector2f(i * texDimensions.x, currBot);

			model[4 * ((i * rows) + j)].texCoords = sf::Vector2f(0.f, tilemap[i * rows + j] * texDimensions.y);
			model[4 * ((i * rows) + j) + 1].texCoords = sf::Vector2f(texRight, tilemap[i * rows + j] * texDimensions.y);
			model[4 * ((i * rows) + j) + 2].texCoords = sf::Vector2f(texRight, texBot);
			model[4 * ((i * rows) + j) + 3].texCoords = sf::Vector2f(0.f, texBot);
		}
	}
	modelSize = rows * columns * 4;
}
void Terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (textureSheet) {
		states.texture = textureSheet;
		states.transform = this->getTransform();
		target.draw(model, modelSize, sf::Quads, states);
	}
}