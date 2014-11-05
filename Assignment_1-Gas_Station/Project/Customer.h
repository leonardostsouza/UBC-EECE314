#include "rt.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <random>

#define DIFFERENT_FUEL_TYPES 4
#define CAR_FUEL_CAPACITY 70
#define FUEL_MINIMUM_AMOUNT 30

#define CARD_NUMBER_LEN 16
#define MAXIMUM_NAME_LEN 30

#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer{
public:
	Customer();
	~Customer();

	void copy(Customer);				// copies values from another Customer Object

	unsigned int selectFuel();			// selects the grade of fuel
	unsigned int selectFuelAmount();	// returns the Amount of fuel in liters
	bool makePayment();					// returns true after payment is complete

	std::string getCardNumber();		// returns card number variable
	std::string getName();			// returns name variable

private:
	void setCardNumber();
	void setName();

	std::string name;
	std::string cardNumber;
};
#endif