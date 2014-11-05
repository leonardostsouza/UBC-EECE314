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


class Customer : public ActiveClass{
public:
	Customer();
	~Customer();

	unsigned int selectFuel();			// selects the grade of fuel
	unsigned int selectFuelQuantity();	// returns the quantity of fuel in liters
	bool makePayment();			// returns true after payment is complete

	std::string getCardNumber();		// returns card number variable
	std::string getName();			// returns name variable

	//char* getCardNumber();			// returns card number variable
	//char* getName();				// returns name variable

	int main();

private:
	void setCardNumber();
	void setName();
	

	std::string name;
	std::string cardNumber;

	//char name[MAXIMUM_NAME_LEN];
	//char cardNumber[CARD_NUMBER_LEN];
	

	/*char* name;
	char* cardNumber[];*/

	//std::vector<std::string> possibleNames; //{ "Anna", "Bernard", "Charlie", "Diego", "Emma", "Ferdinand", "George", "Hanna", "Irina", "John", "Kelly", "Lucas", "Michael", "Natasha"};
	//std::vector<std::string> possibleSurnames; //{ "Almund", "Balkan", "Corleone", "Dorca", "Erwin", "Fawkes", "Gear", "Hail", "Ivanovich", "Jackson", "Korolev", "Lombardi", "Moore", "Nash" };
};

#endif