#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
class TextureManager
{
private:
	//maps a texture name to a pair(metadata, textureAddress).
	std::unordered_map<std::string, std::pair<std::vector<int>*, sf::Texture*>> textures;
public:
	std::pair<std::vector<int>*, sf::Texture*> getTextureInfo(std::string name);
	TextureManager();
	//pass in a vector of names, for example ["knight", "goblin", "demon"].
	TextureManager(std::vector<std::string> names);
	//or, pass in names one at a time
	void importTexture(std::string name);
	~TextureManager();
};

