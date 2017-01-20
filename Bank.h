#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

class Tellers {
public:
	Tellers();
	Tellers(int ID);
	~Tellers();

	//Public Methods
	void resetStatus(bool busy); //reset the status of the teller
	int createTellerVector(); //create a vector of tellers waiting to serve
	bool getStatus(); //get the status of a teller; returns true if helping, false if not
	//int getAvgTime(); //get total average time of customers helped after simulation
	int getCustomers(); //get total number of customers helped;
	int getTellerID(); //return the ID of the teller
	void printTellers(); //print out the list of tellers; if too high, more than about 10, then don't print
	int busyTime; //Takes the time of the next customer as busy time and stays active for that long
	int customersHelped; //number of customers a teller has helped
	std::vector<Tellers> tellerCounter; //vector holding all of the created tellers

private:
	//Private Values
	int tellerID; //id number of the teller
	bool helpingStatus; //status of the teller; whether or not they are helping a customer
	//int avgHelpTime; //average help time of this teller

};

class Customers {
public:
	//Customer constructor
	Customers();
	Customers(int ID, int transTime);
	~Customers();

	//Public Methods
	int createLine(std::queue<Customers>& line, int numOfCustomers); //create line of customers with random transaction times
	int createLineOneMinute(std::queue<Customers>& line, int numOfCustomers); //create line where everyone has 1 minute transaction time
	int getCustomerID(); //get customer ID number
	int getTransactionTime(); //get transaction time of customer
	void printCustomers(std::queue<Customers>& line); //print out the customers, testing method

	//Public Values
	int waitTime;
	int custID; //customer ID identifier
	int transactionTime; //customer transaction time spent with teller in minutes

private:
	//Private Values
	std::vector<Customers> line; //vector of customers to be fed into a queue
	//std::queue<Customers> line; //queue of customers that represents bank line
};

/*
All Teller Methods Start Here
-----------------------------
*/
Tellers::Tellers() {}

Tellers::Tellers(int ID) {
	helpingStatus = false;
	tellerID = ID;
	customersHelped = 0;
	busyTime = 0;
}

Tellers::~Tellers() {}

void Tellers::resetStatus(bool busy) {
	helpingStatus = busy;
}

int Tellers::createTellerVector() {
	int numOfTellers;

	std::cout << "How many Tellers would you like? Enter an integer: ";
	std::cin >> numOfTellers;
	assert(numOfTellers > 0 && numOfTellers <= 100);
	for (int i = 0; i < numOfTellers; i++) {
		Tellers teller(i + 1);
		tellerCounter.push_back(teller);
	}

	std::cout << "Created " << numOfTellers << " teller(s) for simulation.\n";

	return numOfTellers;
}

void Tellers::printTellers() {
	std::cout << "Printing the Tellers...\n";
	for (int i = 0; i < tellerCounter.size(); i++) {
		std::cout << "Teller #" << tellerCounter[i].tellerID << " Customers Helped = " << tellerCounter[i].customersHelped << "\n";
	}
}

int Tellers::getCustomers() {
	return customersHelped;
}

int Tellers::getTellerID() {
	return tellerID;
}

bool Tellers::getStatus() {
	return helpingStatus;
}

/*
All Customer Methods Located Below
----------------------------------
*/
Customers::Customers() {}

Customers::Customers(int ID, int transTime) {
	custID = ID;
	transactionTime = transTime;
	waitTime = 0;
}

Customers::~Customers() {}

int Customers::createLine(std::queue<Customers>& line, int numOfCustomers) {
	//random seed
	srand(time(NULL));
	int randTime;

	for (int i = 0; i < numOfCustomers; i++) {
		randTime = rand() % 10 + 1;
		Customers customer(i + 1, randTime);
		line.push(customer);
	}

	return numOfCustomers;
}

int Customers::createLineOneMinute(std::queue<Customers>& line, int numOfCustomers) {
	for (int i = 0; i < numOfCustomers; i++) {
		Customers customer(i + 1, 1);
		line.push(customer);
	}

	return numOfCustomers;
}

void Customers::printCustomers(std::queue<Customers>& line) {
	Customers c;
	std::cout << "Printing the Customers...\n";
	while (!line.empty()) {
		c = line.front();
		std::cout << "Customer #" << c.custID << " Customers Transaction Time = " << c.transactionTime << "\n";
		line.pop();
	}
}

int Customers::getCustomerID() {
	return custID;
}

int Customers::getTransactionTime() {
	return transactionTime;
}