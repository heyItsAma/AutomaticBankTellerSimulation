#include <iostream>
#include <queue>
#include "Bank.h"
#include "Simulation.h"

//The queue line is defined here and passed by reference to simulation. 
typedef std::queue<Customers> line;

int main() {
	//Create a queue to reference to in other functions.
	std::queue<Customers> line;

	Simulation sim;
	sim.runSimulation(line);
	return 0;
}