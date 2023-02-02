#include <SFML/Graphics.hpp>
#include <typeinfo>
#include "collision.h";
#include <math.h>
#include "Interactable.h"
bool collidesRectCirc(sf::RectangleShape* rect, sf::CircleShape* circ) {
	sf::Vector2f circleCenter;
	float circleRadius = circ->getRadius();
	circleCenter.x = circ->getPosition().x + circleRadius;
	circleCenter.y = circ->getPosition().y + circleRadius;
	float rectTop = rect->getGlobalBounds().top;
	float rectBot = rect->getGlobalBounds().top + rect->getGlobalBounds().height;
	float rectLeft = rect->getGlobalBounds().left;
	float rectRight = rect->getGlobalBounds().left + rect->getGlobalBounds().width;

	//RECTANGLE_CIRCLE_COLLISION
	//problem: sticky corners
	//inside
	if (((circleCenter.x > rectLeft) && (circleCenter.x < rectRight)) && ((circleCenter.y > rectTop) && circleCenter.y < rectBot))
		return true;
	//above
	if ((circleCenter.y - rectTop <= 0) && (circleCenter.x - rectLeft >= 0) && (circleCenter.x - rectRight <= 0))
		if (rectTop - circleCenter.y - circleRadius <= 0.001f)
			return true;

	//left
	if ((circleCenter.x - rectLeft <= 0) && (circleCenter.y - rectTop >= 0) && (circleCenter.y - rectBot <= 0))
		if (rectLeft - circleCenter.x - circleRadius <= 0.001f)
			return true;
	//right
	if ((circleCenter.x - rectRight >= 0) && (circleCenter.y - rectTop >= 0) && (circleCenter.y - rectBot <= 0))
		if (circleCenter.x - rectRight - circleRadius <= 0.001f)
			return true;
	//under
	if ((circleCenter.y - rectBot >= 0) && (circleCenter.x - rectLeft >= 0) && (circleCenter.x - rectRight <= 0))
		if (circleCenter.y - rectBot - circleRadius <= 0.001f)
			return true;
	//upper-right
	if ((circleCenter.x - rectRight >= 0) && (circleCenter.y - rectTop <= 0)) {
		if (sqrt(pow(circleCenter.x - rectRight, 2) + pow(rectTop - circleCenter.y, 2)) <= circleRadius) {
			return true;
		}

	}

	//upper-left
	if ((circleCenter.x - rectLeft <= 0) && (circleCenter.y - rectTop <= 0)) {
		if (sqrt(pow(circleCenter.x - rectLeft, 2) + pow(rectTop - circleCenter.y, 2)) <= circleRadius) {
			return true;
		}
	}
	//lower-right
	if ((circleCenter.x - rectRight >= 0) && (circleCenter.y - rectBot >= 0)) {
		if (sqrt(pow(circleCenter.x - rectRight, 2) + pow(rectBot - circleCenter.y, 2)) <= circleRadius) {
			return true;
		}
	}
	//lower-left
	if ((circleCenter.x - rectLeft <= 0) && (circleCenter.y - rectBot >= 0)) {
		if (sqrt(pow(circleCenter.x - rectLeft, 2) + pow(rectBot - circleCenter.y, 2)) <= circleRadius) {
			return true;
		}
	}
	return false;
}
bool collidesRectSprite(sf::RectangleShape* rect, sf::Sprite* sprite) {
	return false;
}
bool collidesRectRect(sf::RectangleShape* first, sf::RectangleShape* second) {
	sf::FloatRect firstBounds = first->getGlobalBounds();
	sf::FloatRect secondBounds = second->getGlobalBounds();
	float xminF = firstBounds.left;
	float xmaxF = firstBounds.left + firstBounds.width;
	float xminS = secondBounds.left;
	float xmaxS = secondBounds.left + secondBounds.width;
	float yminF = firstBounds.top + firstBounds.height;
	float ymaxF = firstBounds.top;
	float yminS = secondBounds.top + secondBounds.height;
	float ymaxS = secondBounds.top;
	if ((((xmaxF > xminS) && (xminF < xminS)) || ((xmaxS > xminF) && (xmaxS < xmaxF))) && (((ymaxF < yminS) && (yminF > yminS)) || ((ymaxS < yminF) && (ymaxS > ymaxF))))
		return true;
	else
		return false;
}
bool collidesCircSprite(sf::CircleShape* circ, sf::Sprite* sprite) {
	return false;
}
bool collidesCircCirc(sf::CircleShape* first, sf::CircleShape* second) {
	float fRadius = first->getRadius();
	float sRadius = second->getRadius();
	sf::Vector2f fCenter = sf::Vector2f(first->getPosition().x + fRadius, first->getPosition().y + fRadius);
	sf::Vector2f sCenter = sf::Vector2f(second->getPosition().x + sRadius, second->getPosition().y + sRadius);
	if (sqrt(pow(fCenter.x - sCenter.x, 2) + pow(fCenter.y - sCenter.y, 2)) < (fRadius + sRadius))
		return true;
	else
		return false;
}
bool collidesSpriteSprite(sf::Sprite*first , sf::Sprite*second) {
	return false;
}
bool collides(sf::Transformable* first, sf::Transformable* second) {
	//confusing, and also not finished yet...
	if ((typeid(*first) == typeid(sf::RectangleShape)) || ((typeid(*first) == typeid(Interactable)) && ((Interactable*) first)->getHitbox()->getShapeType() == 1)) {
		if (typeid(*second) == typeid(sf::CircleShape)) {
			return collidesRectCirc((sf::RectangleShape*) first, (sf::CircleShape*) second);
		}
		if (typeid(*second) == typeid(sf::RectangleShape)) {
			return collidesRectRect((sf::RectangleShape*) first, (sf::RectangleShape*) second);
		}
		if (typeid(*second) == typeid(sf::Sprite)) {
			return collidesRectSprite((sf::RectangleShape*) first, (sf::Sprite*) second);
		}
	}
	//if second is rectangle shape or has a rectangular hitbox...
	else if (typeid(*second) == typeid(sf::RectangleShape)) {
		if (typeid(*first) == typeid(sf::CircleShape)) {
			return collidesRectCirc((sf::RectangleShape*) second, (sf::CircleShape*) first);
		}
		if (typeid(*first) == typeid(sf::Sprite)) {
			return collidesRectSprite((sf::RectangleShape*) second, (sf::Sprite*) first);
		}
	}
	//if first is circle or has circular hitbox...
	else if (typeid(*first) == typeid(sf::CircleShape)) {
		if (typeid(*second) == typeid(sf::CircleShape)) {
			return collidesCircCirc((sf::CircleShape*) first, (sf::CircleShape*) second);
		}
		if (typeid(*second) == typeid(sf::Sprite)) {
			return collidesCircSprite((sf::CircleShape*) first, (sf::Sprite*) second);
		}
	}
	//if second is circle or has circular hitbox...
	else if (typeid(*second) == typeid(sf::CircleShape)) {
		if (typeid(*first) == typeid(sf::Sprite)) {
			return collidesCircSprite((sf::CircleShape*) second, (sf::Sprite*) first);
		}
	}
	//if first and second are sprites...
	else if ((typeid(*first) == typeid(sf::Sprite)) && (typeid(*second) == typeid(sf::Sprite))) {
		return collidesSpriteSprite((sf::Sprite*) first, (sf::Sprite*) second);
	}
	else {
		return false;
	}
}