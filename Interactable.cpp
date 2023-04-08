#include "Interactable.h"
#include "collision.h"
#include "moves.h"
Interactable::~Interactable() {
	delete hitbox;
	delete[] model;
}
Interactable::Interactable() {
	float tempInfo[] = { 0.f, 0.f, 10.f };
	hitbox = new Hitbox(tempInfo, 0);
	this->setPosition(0.f, 0.f);
}
Interactable::Interactable(sf::Vector2f _position, float hitboxRadius, bool visibleHitbox) {
	float hitInfo[3];
	hitInfo[0] = _position.x;
	hitInfo[1] = _position.y;
	hitInfo[2] = hitboxRadius;
	hitbox = new Hitbox(hitInfo, 0, visibleHitbox);
	this->setPosition(_position);
}
Interactable::Interactable(sf::Vector2f _position, float hitboxWidth, float hitboxHeight, bool visibleHitbox) {
	float hitInfo[4];
	hitInfo[0] = _position.x;
	hitInfo[1] = _position.y;
	hitInfo[2] = hitboxWidth;
	hitInfo[3] = hitboxHeight;
	hitbox = new Hitbox(hitInfo, 1, visibleHitbox);
	this->setPosition(_position);
}
bool Interactable::collidesWith(Interactable* other) {
	return collides(this->hitbox->getHitShape(), other->hitbox->getHitShape());
}
Hitbox* Interactable::getHitbox() const{
	return hitbox;
}
void Interactable::importTexture(std::pair<std::vector<int>*, sf::Texture*> textureInfo) {
	textureSheet = textureInfo.second;
	texWidth = textureInfo.first->at(0);
	texHeight = textureInfo.first->at(1);
	for (int i = 0; i < textureInfo.first->at(2); i++) {
		frameNumbers.push_back(textureInfo.first->at(i + 3));
	}
}
void Interactable::setTexturePosition(sf::Vector2i texPos) {
	model[0].position = sf::Vector2f(0.f, 0.f);
	model[1].position = sf::Vector2f(dimensions.x, 0.f);
	model[2].position = sf::Vector2f(dimensions.x, dimensions.y);
	model[3].position = sf::Vector2f(0.f, dimensions.y);

}
void Interactable::setTextureCoords(sf::Vector2i texCoords) {
	texturePosition.x = texCoords.x;
	texturePosition.y = texCoords.y;
	model[0].texCoords = sf::Vector2f((float)texturePosition.x, (float)texturePosition.y);
	model[1].texCoords = sf::Vector2f((float)texturePosition.x + texWidth, (float)texturePosition.y);
	model[2].texCoords = sf::Vector2f((float)texturePosition.x + texWidth, (float)texturePosition.y + texHeight);
	model[3].texCoords = sf::Vector2f((float)texturePosition.x, (float)texturePosition.y + texHeight);
}
sf::Vector2i Interactable::getTexturePosition() {
	return texturePosition;
}
sf::Vector2i Interactable::getTextureDimensions() {
	return sf::Vector2i(texWidth, texHeight);
}
std::vector<int>* Interactable::getFrameNumbers(){
	return &(frameNumbers);
}
void Interactable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (textureSheet) {
		if(getHitbox()->getVisible())
			target.draw(*(getHitbox()->getHitShape()), states);
		states.texture = textureSheet;
		states.transform = this->getTransform();
		target.draw(model, modelSize, sf::Quads, states);
	}
	else {
		
	}
}
sf::Texture* Interactable::getTexture() {
	return textureSheet;
}
sf::Vertex* Interactable::getModel() {
	return model;
}
void Interactable::setTextureModel(sf::Vertex* _model, int _modelSize) {
	model = _model;
	modelSize = _modelSize;
}
