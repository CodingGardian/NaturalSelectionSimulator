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
	srand(time(NULL)); // generate random seed
	this->id = rand() % 100 + 1;
}

creature::creature() {
	point = new Point<creature>();
}

creature::creature(mutation m) : speed(m.speedm), size(m.sizem) {
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

void graphicsSimulator::placeFruit() {
	srand(time(NULL));
	int x = rand() % 100 + 1; // generate random number
	int y = rand() % 100 + 1;
	fruit * temp = new fruit(); // create fruit pointer pointing to a memory adress
	Point<fruit> * temp2 = new Point<fruit>(temp, x, y);
	fruitPoints.push_back(temp2); // store Points<fruit>
}

void graphicsSimulator::createCreature() {
	srand(time(NULL)); 
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	creature * temp = new creature();
	Point<creature> * temp2 = new Point<creature>(temp, x, y);
	creaturePoints.push_back(temp2);
}

void graphicsSimulator::createCreature(mutation m) {
	srand(time(NULL));
	int x = rand() % 100 + 1;
	int y = rand() % 100 + 1;
	creature * temp = new creature(m);
	Point<creature> * temp2 = new Point<creature>(temp, x, y);
	creaturePoints.push_back(temp2);
}

// get functions
Point<creature>* creature::getRefrencePoint() {
	return point;
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

bool creature::foodFound() {
	Point<fruit> Fruit = manager::checkClosestPoint<fruit, creature>(fruitPoints, point);

	if (point->x < (Fruit.x + 2) && point->x >(Fruit.x - 2) && point->y > (Fruit.y - 2) && point->y < (Fruit.y + 2)) {
		return true;
	}
	return false;
}

void creature::findFood() {
	srand(time(NULL));

	while (energy > 0) {
		int tempx = rand() % 5 - 2;
		int tempy = rand() % 5 - 2;

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
		std::cout << point->x << "," << point->y << std::endl; 
		
		if (foodFound()) {
			food++;
		}
	}
}
