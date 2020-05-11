#pragma once
#pragma warning(disable : 4244)

#include <utility>
#include <vector>
#include <cmath>

struct mutation;

class creature;
class fruit;

template<class T>
struct Point;



namespace manager { // a namespace for managing the game
	mutation createMutation(); // creates mutation for creature
	void live(creature c); // decides if a creature will live
	
	template<typename T, typename X>
	Point<T> checkClosestPoint(std::vector<Point<T>*> vec, Point<X> * point);
};
