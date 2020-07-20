#include "GraphicsSimulator.h"
#include <iostream>

/* 
	Survival Of the fittest
	========================
	this is a natural selection simulator that I made based off of a video I saw. Basically, you have a bunch or creatures, and these creatures compete for food on a virtual plane, you collect food, you get to live!!! you collect two food, you get to reprodice, you collect no food, you, well, die. You have a random chance to get a mutation that gives you speed, which increases speed, size, which allows you to eat other creatures, or luck, which gives you a chance to live after collecting no food. your offspring will carry your stats, and have a chance of getting stronger stats, so run the simulation, and see what you get!!!
	=========================
*/


int main() {
	srand(time(0));
	

	graphicsSimulator::startTest();
	std::cout << "speed " << "size " << "luck " << std::endl;
	

	for (int i = 0; i < creaturePoints.size(); i++) {
		std::cout << creaturePoints[i]->occupied->getSpeed() << ", " << creaturePoints[i]->occupied->getSize() << ", " << creaturePoints[i]->occupied->getLuck() << std::endl;
	}
	std::cout << "number of creatures after" << std::endl;
	std::cout << creaturePoints.size() << std::endl;
}
