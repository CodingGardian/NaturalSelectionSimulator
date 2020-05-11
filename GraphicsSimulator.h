#pragma once
#pragma warning(disable : 4244)

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#include "Manager.h"

class creature;

template <class T>
struct Point { // a point class for reading position
	Point() {}
	Point(T * temp, int tempx, int tempy);
	T * occupied = nullptr;
	int x = 0;
	int y = 0;

	Point<creature> operator=(const Point<creature>& point);
};

template <>
struct Point <creature> {
	Point() {}
	Point(creature * temp, int tempx, int tempy);
	creature * occupied = nullptr;
	int x = 0;
	int y = 0;

	Point<creature> operator=(const Point<creature>& point);
};

template<>
struct Point <fruit> {
	Point() {}
	Point(fruit * temp, int tempx, int tempy);
	fruit * occupied = nullptr;
	int x = 0;
	int y = 0;

	Point<fruit> operator=(const Point<fruit>& point);
};

class fruit { // food for mutant, will try to eat
public:
	fruit();
	int id;
	float xPos;
	float yPos;


};



struct mutation { // mutation to specify how the creature is afected
	int speedm;
	int sizem;
	int luckm;
};


class creature { // creature class
private:
	Point<creature>* point;
	int speed = 1;
	int size = 1;
	int luck = 0;
	int energy = 50;
	int food = 0;
public:

	creature operator=(creature c);

	creature();
	creature(mutation m);

	void findFood();
	bool foodFound();

	Point<creature>* getRefrencePoint();
	creature* getThis() { return this; }
	int getSpeed();
	int getSize();
	int getEnergy();
	int getFood();

	friend struct Point<creature>;
};



extern std::vector<Point<creature>*> creaturePoints; //these vectors hold all of the objects and their cordinates
extern std::vector<Point<fruit>*> fruitPoints;

namespace graphicsSimulator { // a namespace for simulating the graphics in the video
	constexpr int height = 100; // simple width and height cordinates
	constexpr int width = 100;
	
	void placeFruit(); // places fruit aat random
	void createCreature(); // places creature at random
	void createCreature(mutation m);
};
