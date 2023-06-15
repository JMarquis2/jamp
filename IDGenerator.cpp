#include "IDGenerator.h"
int IDGenerator::getID() {
	currentID++;
	return currentID - 1;
}
void IDGenerator::setID(int initialID) {
	currentID = initialID;
}
int IDGenerator::currentID = 0;