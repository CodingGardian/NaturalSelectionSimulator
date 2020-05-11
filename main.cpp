#include <iostream>
#include "GraphicsSimulator.h"

#pragma warning(disable : 4244)

int main() {
	graphicsSimulator::createCreature();
	creaturePoints[0]->occupied->findFood();

	std::cin.get();
}
