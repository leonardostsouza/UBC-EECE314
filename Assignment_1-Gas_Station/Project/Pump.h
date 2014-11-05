#include "Customer.h"
#include <stdlib.h>

#ifndef PUMP_STATUS_H
#define PUMP_STATUS_H

#define MAX_NAME_LEN 30
#define MAX_CARD_LEN 17		// 16 numbers + '/0'

typedef struct pumpStatus{
	char customerName[MAX_NAME_LEN];
	char customerCC[MAX_CARD_LEN];		//Credit Card Numer
	unsigned int selectedFuel;			// Fuel Chosen by the customer
	unsigned int selectedFuelAmount;	// amount of fuel being filled
	float priceToPay;					// price to be paid by the customer
	unsigned int status;				// 0 = free; 1 = selecting fuel; 2 = selecting amount; 3 = dispensing fuel; 4 = waiting to be free; 5 = waiting for payment
};

typedef struct customerStatus{
	char customerName[MAX_NAME_LEN];
	char customerCC[MAX_CARD_LEN];		//Credit Card Numer
	unsigned int selectedFuel;			// Fuel Chosen by the customer
	unsigned int selectedFuelAmount;	// amount of fuel being filled
};

typedef struct fuelTankStatus{
	unsigned int currentFuelVolume;
	float fuelPrice;
};
#endif

#ifndef PUMP_H
#define PUMP_H

#define PUMP_PIPE_SIZE 2048
#define FUEL_BASE_PRICE 1.70

class Pump{
public:
	Pump();
	~Pump();

	void setSelectedFuel(unsigned int);
	void setSelectedFuelAmount(unsigned int);
	void setPriceToPay();

	unsigned int getSelectedFuel();
	unsigned int getSelectedFuelAmount();

	unsigned int getTankFuelAmount();

	float getPriceToPay();
	bool isPaid();

	void receivePayment();
	void fillCustomer();			// fills the Customer with fuel

	void setFuelPrice(unsigned int, float); // changes selected fuel price
	float getFuelPrice(unsigned int); // returns selected fuel price

private:
	unsigned int selectedFuel;
	unsigned int selectedFuelAmount;

	float priceToPay;
	bool paimentReceived;

	static float fuel1Price;
	static float fuel2Price;
	static float fuel3Price;
	static float fuel4Price;
};
#endif