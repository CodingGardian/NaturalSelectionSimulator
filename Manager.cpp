#include "Manager.h"

template<typename T, typename X> Point<T> manager::checkClosestPoint(std::vector<Point<T>*> vec, Point<X> * point) {
	std::pair<Point<T>, int> returnVal;
	returnVal.second = 100; // set to 100 because max value can only be 100
	
	for (Point<T> * a : vec) {
		int x = sqrt(((a->x * a.x) - (point->x * point->x)) + ((a->y * a->y) - (point->y * point->y)));
		abs(x);
		if (x < returnVal.second) {
			returnVal.first = a;
			returnVal.second = x;
		}
	}
	
	return returnVal.first;
}


