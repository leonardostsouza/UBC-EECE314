#include "Customer.h"

#ifndef PUMP_H
#define PUMP_H



typedef struct pumpStatus{
	char customerName[MAXIMUM_NAME_LEN];
	char customerCC[CARD_NUMBER_LEN];		//Credit Card Numer
	unsigned int fuelType;		// Fuel Chosen by the customer
	unsigned int fuelAmount;	// amount of fuel being filled
};

typedef struct customerCar {
	char name[MAXIMUM_NAME_LEN];
	char card[CARD_NUMBER_LEN];
	unsigned int fuelType;
	unsigned int fuelAmount;
};

class Pump : public ActiveClass {
public:
	Pump(CPipe _pipe, pumpStatus* _poolPtr, CSemaphore _producerPipe, CSemaphore _consumerPipe, CSemaphore _producerPool, CSemaphore _consumerPool){
		pipe = &_pipe;
		poolPtr = _poolPtr;

		producerPipe = &_producerPipe;
		producerPipe = &_consumerPipe;
		producerPool = &_producerPool;
		consumerPool = &_consumerPool;
		main();
	}

	//~Pump(){}

	//bool isPaid();			// checks if the Pump has already received payment

	//void receiveCustomer(Customer *);	// receives next Customer on the queue 
	////void makePaiment(Customer *);
	//void fillCustomer();			// fills the Customer with fuel

	int main(void){

		printf("creating c\n");
		customerCar c;			//customer being served
		printf("c created\n");
		// consume data from pipe
		printf("P1 waiting\n");
		producerPipe->Wait();

		pipe->Read(&c, sizeof(c));
		printf("read from pipe\n");

		consumerPipe->Signal();



		// produce data to Datapool
		consumerPool->Wait();

		printf("writing...\n");
		// writing name
		for (int i = 0; i < MAXIMUM_NAME_LEN; i++)
			poolPtr->customerName[i] = c.name[i];
		printf("name = %s\n", poolPtr->customerName);
		// writing card number
		for (int i = 0; i < CARD_NUMBER_LEN; i++)
			poolPtr->customerCC[i] = c.card[i];
		printf("cc = %s\n", poolPtr->customerCC);
		// writing fuelType
		poolPtr->fuelType = c.fuelType;
		printf("fuel type = %s\n", c.fuelType);
		printf("fuel type = %s\n", poolPtr->fuelType);
		// writing fuelAmount
		poolPtr->fuelAmount = c.fuelAmount;
		printf("fuel amount = %s\n", c.fuelAmount);
		printf("fuel amount (liters) = %s\n", poolPtr->fuelAmount);
		printf("done\n");

		producerPool->Signal();

		return 0;
	}

private:
	CPipe *pipe;
	pumpStatus *poolPtr;

	CSemaphore *producerPipe;
	CSemaphore *consumerPipe;
	CSemaphore *producerPool;
	CSemaphore *consumerPool;

	bool paiment;			// true = received paiment; false = waiting for paiment
	Customer *inServiceCustomer;		// Customer in service at the moment
	
};


#endif