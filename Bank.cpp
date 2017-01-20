#include "Bank.h"
#include <queue>
#include <assert.h>

/*
	All Teller Methods Start Here
	-----------------------------
*/
Tellers::Tellers(){}

Tellers::Tellers(int ID){
		helpingStatus = false;
		tellerID = ID;
		customersHelped = 0;
		busyTime = 0;
}

Tellers::~Tellers(){}

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
Customers::Customers(){}

Customers::Customers(int ID, int transTime){
	custID = ID;
	transactionTime = transTime;
	waitTime = 0;
}

Customers::~Customers(){}

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
	while(!line.empty()){
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