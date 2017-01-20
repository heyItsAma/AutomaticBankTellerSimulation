#pragma once
#include <iostream>
#include <assert.h>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include "Bank.h"

/*
	This header files contains all simulation info.
	Here is where the simulation is developed.
	1. The user is asked for a total simulation time in minutes to run the program. (check!)
	2. The user is asked for the number of customers and tellers. (check!)
	3. Each customer has a random transaction time, which must be collected and stored
		to be averaged at the end of the simulation. 
	4. When a teller is done (when the minutes with each transaction finish), they
		drop the customer, become active, then pick up another if the simulation
		time is not over. The program continues until the simulation time equals
		the time passed.
*/

class Simulation {
public:
	Simulation();
	~Simulation();

	void runSimulation(std::queue<Customers>& line); //run the simulation, ask user for inputs, run while loop
};

Simulation::Simulation(){}

Simulation::~Simulation(){}

void Simulation::runSimulation(std::queue<Customers>& line) {
	//Variables
	int start = 0; //time starts at zero
	int sim_time; //this is the simulation time given by the user
	int totalServiceTime = 0;
	int avgServiceTime = 0;
	int customerCounter = 0;
	int custID = 0;
	int numOfCustomers;
	int numOfTellers;
	int totalCustomersServed = 0;
	int customersPerMinute;
	int totalDepartureTime = 0;
	int totalWaitTime = 0;
	bool busy;

	//1. Ask user for total simulation time.
	std::cout << "How long would you like to run the simulation? (Time is in minutes.): ";
	std::cin >> sim_time;
	std::cout << "The program will be run for " << sim_time << " minutes.\n";
	assert(sim_time > 0 && sim_time <= 10000);

	//2. Ask user for number of tellers and number of customers
	//Customers are stored in a queue. Tellers are stored in a vector.
	std::cout << "How many customers would you like? Enter an integer: ";
	std::cin >> numOfCustomers;
	assert(numOfCustomers > 0 && numOfCustomers <= 10000);
	std::cout << "Now creating a line of " << numOfCustomers << " customer(s).\n";
	customersPerMinute = numOfCustomers / sim_time;

	Customers c;
	Tellers t;

	//Print Both Tellers and Customer Queue to test. Cannot run this and another after!
	//c.printCustomers(line);
	//t.printTellers();

	//Create a vector of Tellers
	numOfTellers = t.createTellerVector();

	std::cout << "Would you like to a. generate random transaction times or b. generate a common transaction time of 1 minute? (Type a or b): ";
	char choice;
	std::cin >> choice;

		if (choice == 'a' || choice == 'A') {
			std::cout << "Customers will have random transaction times.\n";

			if (numOfCustomers < 10) {
				//Use when the number of customers < 10
				c.createLine(line, numOfCustomers);

				while ((start < sim_time)) {
					for (int i = 0; i < numOfTellers; i++) {
						if (t.tellerCounter[i].busyTime != 0 && t.tellerCounter[i].getStatus() == true) {
							t.tellerCounter[i].busyTime--;
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == true && !line.empty()) {
							//if the teller is done with the customer
							//1. reset the teller status
							busy = false;
							t.tellerCounter[i].resetStatus(busy);
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == false && !line.empty()) {
							//if the teller is not busy all together
							//1. take a customer
							//2. set status to busy = true
							//3. set busy time to customer time
							//4. add to served customers
							//5. pop the customer
							c = line.front();
							std::cout << "Teller #" << i + 1 << " is taking Customer #" << c.custID << ". Customer's Transaction Time = " << c.transactionTime << "\n";
							busy = true;
							t.tellerCounter[i].resetStatus(busy);
							t.tellerCounter[i].busyTime = c.getTransactionTime();
							totalServiceTime += c.getTransactionTime();
							t.tellerCounter[i].customersHelped++;

							//calculate departure time
							c.waitTime = start + c.getTransactionTime();
							totalDepartureTime += c.waitTime;
							std::cout << "Customer #" << c.custID << " waited " << c.waitTime << " minutes before departing.\n";
							line.pop();
						}
					}

					//calculate wait time
					totalWaitTime += (totalDepartureTime - start);

					//Increment the start time by 1 unit (1 minute).
					start++;
					//At every minute, more customers are pushed into the queue.
					std::cout << "Minute " << start << ". ";
					//std::cout << "Adding " << customersPerMinute << " more customers to the queue.\n";
					//c.createLine(line, customersPerMinute);
				}
			}
			else if (numOfCustomers >= 10) {
				//When the number of customers == 10 or more
				c.createLine(line, customersPerMinute);

				while ((start < sim_time)) {
					for (int i = 0; i < numOfTellers; i++) {
						if (t.tellerCounter[i].busyTime != 0 && t.tellerCounter[i].getStatus() == true) {
							t.tellerCounter[i].busyTime--;
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == true && !line.empty()) {
							//if the teller is done with the customer
							//1. reset the teller status
							busy = false;
							t.tellerCounter[i].resetStatus(busy);
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == false && !line.empty()) {
							//if the teller is not busy all together
							//1. take a customer
							//2. set status to busy = true
							//3. set busy time to customer time
							//4. add to served customers
							//5. pop the customer
							c = line.front();
							std::cout << "Teller #" << i + 1 << " is taking Customer #" << c.custID << ". Customer's Transaction Time = " << c.transactionTime << "\n";
							busy = true;
							t.tellerCounter[i].resetStatus(busy);
							t.tellerCounter[i].busyTime = c.getTransactionTime();
							totalServiceTime += c.getTransactionTime();
							t.tellerCounter[i].customersHelped++;

							//calculate departure time
							c.waitTime = start + c.getTransactionTime();
							totalDepartureTime += c.waitTime;
							std::cout << "Customer #" << c.custID << " waited " << c.waitTime << " minutes before departing.\n";
							line.pop();
						}
					}

					//calculate wait time
					totalWaitTime += (totalDepartureTime - start);

					//Increment the start time by 1 unit (1 minute).
					start++;
					//At every minute, more customers are pushed into the queue.
					std::cout << "Minute " << start << ". ";
					std::cout << "Adding " << customersPerMinute << " more customers to the queue.\n";
					c.createLine(line, customersPerMinute);
				}
			}

		}
		else if (choice == 'b' || choice == 'B') {

			std::cout << "All customers will have a transaction time of 1 minute.\n";

			if (numOfCustomers < 10) {
				//Use when the number of customers < 10
				c.createLineOneMinute(line, numOfCustomers);

				while ((start < sim_time)) {
					for (int i = 0; i < numOfTellers; i++) {
						if (t.tellerCounter[i].busyTime != 0 && t.tellerCounter[i].getStatus() == true) {
							t.tellerCounter[i].busyTime--;
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == true && !line.empty()) {
							//if the teller is done with the customer
							//1. reset the teller status
							busy = false;
							t.tellerCounter[i].resetStatus(busy);
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == false && !line.empty()) {
							//if the teller is not busy all together
							//1. take a customer
							//2. set status to busy = true
							//3. set busy time to customer time
							//4. add to served customers
							//5. pop the customer
							c = line.front();
							std::cout << "Teller #" << i + 1 << " is taking Customer #" << c.custID << ". Customer's Transaction Time = " << c.transactionTime << "\n";
							busy = true;
							t.tellerCounter[i].resetStatus(busy);
							t.tellerCounter[i].busyTime = c.getTransactionTime();
							totalServiceTime += c.getTransactionTime();
							t.tellerCounter[i].customersHelped++;

							//calculate departure time
							c.waitTime = start + c.getTransactionTime();
							totalDepartureTime += c.waitTime;
							std::cout << "Customer #" << c.custID << " waited " << c.waitTime << " minutes before departing.\n";
							line.pop();
						}
					}

					//calculate wait time
					totalWaitTime += (totalDepartureTime - start);

					//Increment the start time by 1 unit (1 minute).
					start++;
					//At every minute, more customers are pushed into the queue.
					std::cout << "Minute " << start << ". ";
					//std::cout << "Adding " << customersPerMinute << " more customers to the queue.\n";
					//c.createLine(line, customersPerMinute);
				}
			}
			else if (numOfCustomers >= 10) {
				//When the number of customers == 10 or more
				c.createLineOneMinute(line, customersPerMinute);

				while ((start < sim_time)) {
					for (int i = 0; i < numOfTellers; i++) {
						if (t.tellerCounter[i].busyTime != 0 && t.tellerCounter[i].getStatus() == true) {
							t.tellerCounter[i].busyTime--;
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == true && !line.empty()) {
							//if the teller is done with the customer
							//1. reset the teller status
							busy = false;
							t.tellerCounter[i].resetStatus(busy);
						}
						if (t.tellerCounter[i].busyTime == 0 && t.tellerCounter[i].getStatus() == false && !line.empty()) {
							//if the teller is not busy all together
							//1. take a customer
							//2. set status to busy = true
							//3. set busy time to customer time
							//4. add to served customers
							//5. pop the customer
							c = line.front();
							std::cout << "Teller #" << i + 1 << " is taking Customer #" << c.custID << ". Customer's Transaction Time = " << c.transactionTime << "\n";
							busy = true;
							t.tellerCounter[i].resetStatus(busy);
							t.tellerCounter[i].busyTime = c.getTransactionTime();
							totalServiceTime += c.getTransactionTime();
							t.tellerCounter[i].customersHelped++;

							//calculate departure time
							c.waitTime = start + c.getTransactionTime();
							totalDepartureTime += c.waitTime;
							std::cout << "Customer #" << c.custID << " waited " << c.waitTime << " minutes before departing.\n";
							line.pop();
						}
					}

					//calculate wait time
					totalWaitTime += (totalDepartureTime - start);

					//Increment the start time by 1 unit (1 minute).
					start++;
					//At every minute, more customers are pushed into the queue.
					std::cout << "Minute " << start << ". ";
					std::cout << "Adding " << customersPerMinute << " more customers to the queue.\n";
					c.createLineOneMinute(line, customersPerMinute);
				}
			}

		}
		else {
			std::cout << "Please enter 'a' or 'b'.\n";

		}



	/*
			Results of Simulation
	*/
	//Calculate the total number of customers served.
	for (int i = 0; i < numOfTellers; i++) {
		totalCustomersServed += t.tellerCounter[i].customersHelped;
	}

	std::cout << "-------------------------------------------------------------\n";
	std::cout << "Results: \n";
	std::cout << "Total customers served: " << totalCustomersServed << "\n";
	std::cout << "Total transaction time: " << totalServiceTime << " minutes.\n";
	std::cout << "Number of Customers: " << numOfCustomers << "\n";
	std::cout << "Number of Tellers: " << numOfTellers << "\n";
	std::cout << "Simulation time (in minutes): " << sim_time << "\n";

	//Currently my average transaction time is an integer. It may be best to change it to float!
	std::cout << "Average Transaction time is " << totalServiceTime / totalCustomersServed << " minutes.\n";
	std::cout << "Average departure time is " << totalDepartureTime / totalCustomersServed << " minutes.\n";
	std::cout << "Average wait time is: " << totalWaitTime / totalCustomersServed << " minutes.\n";
}