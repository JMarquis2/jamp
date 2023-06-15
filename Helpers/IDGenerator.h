#pragma once
class IDGenerator {
private:
	static int currentID;
public:
	static int getID();
	static void setID(int initialID);
};