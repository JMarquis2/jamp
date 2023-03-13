#include "TextureManager.h"
#include <fstream>
TextureManager::TextureManager() {

}
//this is my texturemanager comment.
TextureManager::TextureManager(std::vector<std::string> names) {
	for (int i = 0; i < names.size(); i++) {
		importTexture(names[i]);
	}
}
TextureManager::~TextureManager() {
	for (auto it = textures.begin(); it != textures.end(); it++) {
		delete it->second.first;
		delete it->second.second;
	}
}
void TextureManager::importTexture(std::string name) {
	sf::Texture* currTexture = new sf::Texture();
	currTexture->loadFromFile("Textures/" + name + ".png");

	std::ifstream myfile("Textures/" + name + ".jampd");
	std::vector<int>* metadata = new std::vector<int>;

	std::string lineData;

	while (getline(myfile, lineData)) {
		metadata->push_back(std::stoi(lineData));
	}
	textures[name].first = metadata;
	textures[name].second = currTexture;
}
std::pair<std::vector<int>*, sf::Texture*> TextureManager::getTextureInfo(std::string name) {
	return textures[name];
}
