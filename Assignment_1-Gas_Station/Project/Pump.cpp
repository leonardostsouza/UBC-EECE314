#include "Pump.h"

Pump::Pump(){
	paimentReceived = false;
	priceToPay = 0;
}
Pump::~Pump(){}
//**************************************************************************************************************************************************
void Pump::setSelectedFuel(unsigned int _fuelType){ selectedFuel = _fuelType; }
void Pump::setSelectedFuelAmount(unsigned int _amount){ selectedFuelAmount = _amount; }

void Pump::setPriceToPay(){
	float price;
	switch (selectedFuel){
	case 1:
		price = fuel1Price;
		break;
	case 2:
		price = fuel2Price;
		break;
	case 3:
		price = fuel3Price;
		break;
	case 4:
		price = fuel4Price;
		break;
	}
	priceToPay = selectedFuelAmount * price;
}
//**************************************************************************************************************************************************
unsigned int Pump::getSelectedFuel(){ return selectedFuel; }
unsigned int Pump::getSelectedFuelAmount(){ return selectedFuelAmount; }

float Pump::getPriceToPay(){ return priceToPay; }
bool Pump::isPaid(){ return paimentReceived; };
//**************************************************************************************************************************************************
void Pump::receivePayment(){
	SLEEP(5000); // Wait for the customer to get his(her) card
	paimentReceived = true;
}

void Pump::fillCustomer(){
	// 0.5 liters/second
	if (paimentReceived){
		UINT time_to_fill = 2 * selectedFuelAmount * 1000;
		SLEEP(time_to_fill);
	}
	else {
		printf("Cannot fill customer's car. Customer did NOT pay!");
	}
}



//**************************************************************************************************************************************************

void Pump::setFuelPrice(unsigned int type, float price){
	switch (type){
	case 1: 
		fuel1Price = price;
		break;
	case 2:
		fuel2Price = price;
		break;
	case 3:
		fuel3Price = price;
		break;
	case 4:
		fuel4Price = price;
		break;
	default:
		printf("Invalid fuel type\n");
	}
}

float Pump::getFuelPrice(unsigned int type){
	switch (type){
	case 1:
		return fuel1Price;
		break;
	case 2:
		return fuel2Price;
		break;
	case 3:
		return fuel3Price;
		break;
	case 4:
		return fuel4Price;
		break;
	default:
		printf("Invalid fuel type\n");
	}
}
//**************************************************************************************************************************************************
float Pump::fuel1Price = FUEL_BASE_PRICE;
float Pump::fuel2Price = FUEL_BASE_PRICE + 0.20;
float Pump::fuel3Price = FUEL_BASE_PRICE + 0.40;
float Pump::fuel4Price = FUEL_BASE_PRICE + 0.60;