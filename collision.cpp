#include <SFML/Graphics.hpp>
#include <typeinfo>
#include "collision.h";
#include <math.h>
#include <type_traits>
bool checkAngledRects(std::vector<sf::Vector2f>& firstPoints, std::vector<sf::Vector2f>& secondPoints) {
	for (int i = 0; i < 4; i++) {
		sf::Vector2f edge = firstPoints[i] - firstPoints[(i + 3) % 4];
		float tempf = edge.x;
		edge.x = edge.y;
		edge.y = - tempf;

		//sets sign by comparing edge and another point on first rectangle
		bool sign = !(edge.x * (firstPoints[(i + 1) % 4].x - firstPoints[i].x) + edge.y * (firstPoints[(i + 1) % 4].y - firstPoints[i].y) >= 0.0000001f);
		for (int j = 0; j < 4; j++) {
			//compare edge and a point on the second rectangle
			if (sign != (edge.x * (secondPoints[j].x - firstPoints[i].x) + edge.y * (secondPoints[j].y - firstPoints[i].y)) >= 0.0000001f) {
				break;
			}
			if (j == 3) {
				return false;
			}
		}
	}
	return true;
}
bool collidesRectCirc(sf::RectangleShape* rect, sf::CircleShape* circ) {
	sf::Vector2f circleCenter;
	float circleRadius = circ->getRadius();
	circleCenter.x = circ->getPosition().x + circleRadius;
	circleCenter.y = circ->getPosition().y + circleRadius;
	//if rectangle is axis aligned...
	if (abs(rect->getRotation()) <= 0.00001f) {
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
	//so the rectangle isn't axis-aligned...
	std::vector<sf::Vector2f> rectPoints;
	for (int i = 0; i < 4; i++) {
		sf::Vector2f pointPos;
		pointPos.x = rect->getTransform().transformPoint(rect->getPoint(i)).x;
		pointPos.y = rect->getTransform().transformPoint(rect->getPoint(i)).y;
		rectPoints.push_back(pointPos);
	}
	for (int i = 0; i < 4; i++) {
		//check corner
		if (sqrt(pow((circleCenter.x - rectPoints[i].x), 2) + pow(circleCenter.y - rectPoints[i].y, 2)) <= circleRadius) {
			return true;
		}
		//check side
		sf::Vector2f edgeBackwards = rectPoints[i] - rectPoints[(i + 1) % 4];
		sf::Vector2f edgeForwards = rectPoints[(i + 1) % 4] - rectPoints[i];
		//check if circle lies between rectpoint[i] and rectpoint[i + 1] using dot products
		if ((edgeForwards.x * (circleCenter.x - rectPoints[i].x) + edgeForwards.y * (circleCenter.y - rectPoints[i].y) >= 0.00001f) &&
			(edgeBackwards.x * (circleCenter.x - rectPoints[(i + 1) % 4].x) + edgeBackwards.y * (circleCenter.y - rectPoints[(i + 1) % 4].y) >= 0.00001f)) {
			float slope = edgeForwards.y / edgeForwards.x;
			sf::Vector2f closestPoint;
			closestPoint.x = ((circleCenter.x / slope) + circleCenter.y - rectPoints[i].y + slope * rectPoints[i].x) / ((slope * slope + 1) / slope);
			closestPoint.y = (slope) * (closestPoint.x - rectPoints[i].x) + rectPoints[i].y;

			if (sqrt(pow((circleCenter.x - closestPoint.x), 2) + pow(circleCenter.y - closestPoint.y, 2)) <= circleRadius)
				return true;
		}
	}
	return false;
}
bool collidesRectRect(sf::RectangleShape* first, sf::RectangleShape* second) {
	//check if rectangles are axis-aligned
	if ((abs(first->getRotation()) < 0.00001f) && abs(second->getRotation() < 0.00001f)) {
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

		if ((xminF > xmaxS) || (xmaxF < xminS) || (ymaxF > yminS) || (yminF < ymaxS))
			return false;
		else
			return true;
	}

	//otherwise, we do something else...
	std::vector<sf::Vector2f> firstPoints;
	std::vector<sf::Vector2f> secondPoints;

	for (int i = 0; i < 4; i++) {
		sf::Vector2f pointPos;
		pointPos.x = first->getTransform().transformPoint(first->getPoint(i)).x;
		pointPos.y = first->getTransform().transformPoint(first->getPoint(i)).y;
		firstPoints.push_back(pointPos);

		pointPos.x = second->getTransform().transformPoint(second->getPoint(i)).x;
		pointPos.y = second->getTransform().transformPoint(second->getPoint(i)).y;
		secondPoints.push_back(pointPos);
	}
	if (!checkAngledRects(firstPoints, secondPoints))
		return false;
	if (!checkAngledRects(secondPoints, firstPoints))
		return false;
	return true;
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
bool collides(sf::Shape* first, sf::Shape* second) {
	//if first is a rectangle shape...
	if (typeid(*first) == typeid(sf::RectangleShape)) {
		if (typeid(*second) == typeid(sf::CircleShape)) {
			return collidesRectCirc((sf::RectangleShape*) first, (sf::CircleShape*) second);
		}
		if (typeid(*second) == typeid(sf::RectangleShape)) {
			return collidesRectRect((sf::RectangleShape*) first, (sf::RectangleShape*) second);
		}
	}
	//if second is rectangle shape...
	else if (typeid(*second) == typeid(sf::RectangleShape)) {
		if (typeid(*first) == typeid(sf::CircleShape)) {
			return collidesRectCirc((sf::RectangleShape*) second, (sf::CircleShape*) first);
		}
	}
	//if first is a circle shape...
	else if (typeid(*first) == typeid(sf::CircleShape)) {
		if (typeid(*second) == typeid(sf::CircleShape)) {
			return collidesCircCirc((sf::CircleShape*) first, (sf::CircleShape*) second);
		}
	}
	else {
		return false;
	}
}
bool collides(Interactable* first, Interactable* second) {
	return collides(first->getHitbox()->getHitShape(), second->getHitbox()->getHitShape());
}