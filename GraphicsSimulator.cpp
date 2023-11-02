#include "GraphicsSimulator.h"

#pragma warning(disable : 4244)

std::vector<Point<creature>*> creaturePoints; // forward decleration to specify vectors
std::vector<Point<fruit>*> fruitPoints;

Point<creature> Point<creature>::operator=(const Point<creature>& point) {
	occupied = point.occupied;
	x = point.x;
	y = point.y;
	return point;
}

Point<creature>::Point(creature * temp, int tempx, int tempy) : occupied(temp), x(tempx), y(tempy) {
	temp->point = this;
} // constructor for Point<creature>

Point<fruit>::Point(fruit * temp, int tempx, int tempy) : occupied(temp), x(tempx), y(tempy) {} // construcotr for Point<fruit>

Point<fruit> Point<fruit>::operator=(const Point<fruit>& point) {
	occupied = point.occupied;
	x = point.x;
	y = point.y;
	return point;
}

fruit::fruit() { // constructor for fruit
	
}

creature::creature() {
	point = new Point<creature>();
}

creature::creature(mutation m) : speed(m.speedm), size(m.sizem), luck(m.luckm) {
	point = new Point<creature>();
}

creature creature::operator=(creature c) {
	
	*(this->point) = *(c.point);
	this->speed = c.speed;
	this->size = c.size;
	this->luck = c.luck;
	this->energy = c.energy;
	this->food = c.food;

	return *this;
}

mutation::mutation(int speed, int size, int luck) : speedm(speed), sizem(size), luckm(luck) {}

void graphicsSimulator::placeFruit() {
	int x = rand() % width + 1; // generate random number
	int y = rand() % height + 1;
	fruit * temp = new fruit(); // create fruit pointer pointing to a memory adress
	Point<fruit> * temp2 = new Point<fruit>(temp, x, y);
	fruitPoints.push_back(temp2); // store Points<fruit>
}

void graphicsSimulator::createCreature() { // creates creature
	int x = rand() % width + 1;
	int y = rand() % height + 1;
	creature * temp = new creature();
	Point<creature> * temp2 = new Point<creature>(temp, x, y);
	creaturePoints.push_back(temp2);
}

void graphicsSimulator::createCreature(mutation m) { // creates creature with mutation
	int x = rand() % width + 1;
	int y = rand() % height + 1;
	creature * temp = new creature(m);
	Point<creature> * temp2 = new Point<creature>(temp, x, y);
	creaturePoints.push_back(temp2);
}

mutation graphicsSimulator::createMutation() { // creates mutation
	int speed = rand() % 5 + 1;
	int size = rand() % 5 + 1;
	int luck = rand() % 5 + 1;
	mutation m(speed, size, luck);

	return m;
}

mutation graphicsSimulator::createMutation(creature c) {
/* 
	basically, this creates a mutation based off of the stats of a creature c, if they have. a trait, speed, for say, the mutation created will have speed, but also have a chance to increase
*/
	int i = 0;
	std::string x;
	if (c.getSpeed() > i) { i = c.getSpeed(); x = "speed"; }
	if (c.getSize() > i) { i = c.getSize(); x = "size"; }
	if (c.getLuck() > i) { i = c.getLuck(); x = "Luck"; }
	
	if (x == "speed") {
		mutation returnVal((int)(rand() % 5 + 2), (int)(rand() % 3 + 1), (int)(rand() % 3 + 1));
		return returnVal;
	}
	else if (x == "size") {
		mutation returnVal((int)(rand() % 3 + 1), (int)(rand() % 5 + 2), (int)(rand() % 3 + 1));
		return returnVal;
	}
	else if (x == "luck") {
		if (c.getLuck() < 5) { mutation returnVal((int)(rand() % 3 + 1), (int)(rand() % 3 + 1), (int)(rand() % 5 + 2)); return returnVal; }
		else { mutation returnVal((int)(rand() % 3 + 1), (int)(rand() % 3 + 1), (int)(rand() % 15 + 5)); return returnVal; }
		
	}
	else {
		mutation m((int)(rand() % 2 + 1), (int)(rand() % 2 + 1), (int)(rand() % 2 + 1));
		return m;
	}
}

template<typename T, typename X> Point<T> // this just checks the closest point on the graph to a point
 graphicsSimulator::checkClosestPoint( 
	std::vector<Point<T>*> vec, 
	Point<X> * point) {
	std::pair<Point<T>, int> returnVal;
	returnVal.second = 100; // set to 100 because max value can only be 100

	for (Point<T> * a : vec) {
		int x = sqrt(pow((point->x - a->x), 2) + pow((point->y - a->y), 2));
		abs(x);
		if (x < returnVal.second) {
			returnVal.first = *a;
			returnVal.second = x;
		}
	}

	return returnVal.first;
}

bool graphicsSimulator::live(creature c) {
	if (c.getFood() > 0) {
		if (c.getFood() > 1) {
			mutation m = graphicsSimulator::createMutation(c);
			graphicsSimulator::createCreature(m);
		}
		return true;
	}
	
	if (c.getLuck() > 0) {
		int temp = rand() % 100 + c.getLuck();
		if (temp > 90) { return true; }
	}
	return false;
}

void graphicsSimulator::startTest() {
	for (int i = 0; i <= 55; i++) {
		graphicsSimulator::createCreature();
	}
	std::cout << "number of creatures before" << std::endl;
	std::cout << creaturePoints.size() << std::endl;
	
	for (int i = 0; i < 25; i++) {
		for (int i = 0; i < 55; i++) {
			graphicsSimulator::placeFruit();
		}

		for (int i = 0; i < creaturePoints.size(); i++) {
			creaturePoints[i]->occupied->findFood();
		}
		
		for (int i = 0; i < creaturePoints.size(); i++) {
			if (!live(*(creaturePoints[i]->occupied))) {
				creaturePoints.erase(creaturePoints.begin() + i);
			}
		}
	}
}

// get functions
Point<creature>* creature::getRefrencePoint() {
	return point;
}

int creature::getLuck() {
	return luck;
}

int creature::getSpeed() {
	return speed;
}

int creature::getSize() {
	return size;
}


int creature::getEnergy() {
	return energy;
}

int creature::getFood() {
	return food;
}

bool creature::foodFound() { // checks if a creature finds food
	Point<fruit> Fruit = graphicsSimulator::checkClosestPoint<fruit, creature>(fruitPoints, point);
	if (point->x < (Fruit.x + 1) && point->x >(Fruit.x - 1) && point->y > (Fruit.y - 1) && point->y < (Fruit.y + 1)) {
		Point<fruit> * temp = &Fruit;

		for (int i = 0; i < fruitPoints.size(); i++) {
			if (temp == fruitPoints[i]) {
				fruitPoints.erase(fruitPoints.begin() + i);
			}
		}

		return true;
	}
	else if (size > 1) {
		Point<creature> creature1 = graphicsSimulator::checkClosestPoint<creature, creature>(creaturePoints, point);
		
		if (point->x < (creature1.x + 1) && point->x >(creature1.x - 1) && point->y > (creature1.y - 1) && point->y < (creature1.y + 1)) {
			Point<creature> * temp1 = &creature1;

			for (int i = 0; i < creaturePoints.size(); i++) {
				if (temp1 == creaturePoints[i]) {
					creaturePoints.erase(creaturePoints.begin() + i);
				}
			}
		}
	}
	return false;
}

void creature::findFood() { // tells the creature to find food

	while (energy > 0) {
		int tempx = rand() % 5 - 2;
		int tempy = rand() % 5 - 2;

		tempx *= speed;
		tempy *= speed;

		tempx *= size;
		tempy *= size;

		if (point->x + tempx < 0 || point->y + tempy < 0) {
			point->x += (-1 * tempx);
			point->y += (-1 * tempy);
		}
		else if (point->x + tempx > 100) {
			point->x += (-1 * tempx);
			if (point->y + tempy > 100) {
				point->y += (-1 * tempy);
			}
		}
		else if (point->y + tempy > 100) {
			point->y += (-1 * tempy);
			if (point->x + tempx > 100) {
				point->x += (-1 * tempx);
			}
		}
		else {
			point->x += tempx;
			point->y += tempy;
		}
		energy -= (int)(sqrt((tempx * tempx) + (tempy * tempy)));
		
		if (foodFound()) {

			food++;
		}
	}
	
}
