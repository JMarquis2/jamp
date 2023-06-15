#include "Attack.h"
#include "moves.h"
#include <vector>
#define PI 3.14159265f

//rectangular constructor
Attack::Attack(int _damage, sf::Time _remainingTime, float angle, sf::Vector2f hitPosition, float width, float height, float speed, sf::Vector2f hitboxDisplacement, bool visibleHitbox) : Entity(hitPosition, width, height, speed, angle, hitboxDisplacement, visibleHitbox), damage(_damage), remainingTime(_remainingTime) {

	std::vector<int> cardinals = angleToCardinals(angle);
	sf::Vertex* model = new sf::Vertex[4];
	//up
	if (cardinals[0] == 1) {
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;
		
		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(width, 0);
		model[2].position = sf::Vector2f(width, height);
		model[3].position = sf::Vector2f(0, height);
	}
	//down
	else if (cardinals[1] == 1) {
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;

		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(width, 0);
		model[2].position = sf::Vector2f(width, height);
		model[3].position = sf::Vector2f(0, height);
	}
	//left
	else if (cardinals[2] == 1) {
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;

		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(width, 0);
		model[2].position = sf::Vector2f(width, height);
		model[3].position = sf::Vector2f(0, height);
	}
	//right
	else{
		model[0].color = sf::Color::Red;
		model[1].color = sf::Color::Red;
		model[2].color = sf::Color::Red;
		model[3].color = sf::Color::Red;

		model[0].position = sf::Vector2f(0, 0);
		model[1].position = sf::Vector2f(width, 0);
		model[2].position = sf::Vector2f(width, height);
		model[3].position = sf::Vector2f(0, height);
	}
	setModel(model, 4);
}

//circular constructor 
Attack::Attack(int _damage, sf::Time _remainingTime, sf::Vector2f hitPosition, float angle, float radius, float speed, sf::Vector2f hitBoxDisplacement, bool visibleHitbox) : Entity(hitPosition, radius, speed, angle, hitBoxDisplacement, visibleHitbox), damage(_damage), remainingTime(_remainingTime) {

	
	int numVertices = 50; 
	sf::Vertex* model = new sf::Vertex[numVertices];
	float angleIncrement = 2 * PI / numVertices; // Angle increment for each vertex

	for (int i = 0; i < numVertices; ++i)
	{
		float x = radius * cos(angleIncrement * i);
		float y = radius * sin(angleIncrement * i);

		model[i].color = sf::Color::Red;
		model[i].position = sf::Vector2f(x, y);
	}

	setModel(model, numVertices);

		


}


bool Attack::update(sf::Time elapsed) {
	remainingTime -= elapsed;
	if (remainingTime <= sf::milliseconds(0))
		return false;
	return true;
}
