#include "..\Pump.h"
#include "..\rt.h"
#include "..\Customer.h"
#include <iostream>

using namespace std;
//**************************************************************************************************************************************************
// Control Semaphores
CSemaphore endSimulation("endSimulation", 0, 1);

//**************************************************************************************************************************************************
CRendezvous r1("MyRendezvous", 5);

//**************************************************************************************************************************************************
CSemaphore screenSemaphore("screenSemaphore", 1, 1);

//**************************************************************************************************************************************************
CSemaphore tank1Semaphore("tank1Semaphore", 1, 1);
CSemaphore tank2Semaphore("tank2Semaphore", 1, 1);
CSemaphore tank3Semaphore("tank3Semaphore", 1, 1);
CSemaphore tank4Semaphore("tank4Semaphore", 1, 1);

CSemaphore tank1_GSC_Can_Read("tank1_GSC_Can_Read", 0, 1);
CSemaphore tank2_GSC_Can_Read("tank2_GSC_Can_Read", 0, 1);
CSemaphore tank3_GSC_Can_Read("tank3_GSC_Can_Read", 0, 1);
CSemaphore tank4_GSC_Can_Read("tank4_GSC_Can_Read", 0, 1);

//**************************************************************************************************************************************************
// DataPools for Fuel Tanks
CDataPool tank1DP("Tank1", sizeof(unsigned int));
CDataPool tank2DP("Tank2", sizeof(unsigned int));
CDataPool tank3DP("Tank3", sizeof(unsigned int));
CDataPool tank4DP("Tank4", sizeof(unsigned int));

fuelTankStatus *tank1Ptr = (fuelTankStatus *)(tank1DP.LinkDataPool());
fuelTankStatus *tank2Ptr = (fuelTankStatus *)(tank2DP.LinkDataPool());
fuelTankStatus *tank3Ptr = (fuelTankStatus *)(tank3DP.LinkDataPool());
fuelTankStatus *tank4Ptr = (fuelTankStatus *)(tank4DP.LinkDataPool());

//**************************************************************************************************************************************************
// datapool of pump status
CDataPool pumpDP("Pump2", sizeof(pumpStatus));
pumpStatus *pumpStatusPtr = (pumpStatus *)(pumpDP.LinkDataPool());

//**************************************************************************************************************************************************
CSemaphore prodPipe("pipe2Producer", 0, 1);
CSemaphore consPipe("pipe2Consumer", 1, 1);

CSemaphore prodPool("pool2Producer", 0, 1);
CSemaphore consPool("pool2Consumer", 1, 1);

//**************************************************************************************************************************************************
CPipe Pipe_in("Pipe2_in", PUMP_PIPE_SIZE);

//**************************************************************************************************************************************************
unsigned int getTankFuelAmount(unsigned int selectedFuel, unsigned int selectedFuelAmount){
	unsigned int availableAmount;
	switch (selectedFuel){
	case 1:
		tank1Semaphore.Wait();
		availableAmount = tank1Ptr->currentFuelVolume;
		if (availableAmount > 200){
			tank1Ptr->currentFuelVolume = availableAmount - selectedFuelAmount;
		}
		tank1_GSC_Can_Read.Signal();
		tank1Semaphore.Signal();
		break;
	case 2:
		tank2Semaphore.Wait();
		availableAmount = tank2Ptr->currentFuelVolume;
		if (availableAmount > 200){
			tank2Ptr->currentFuelVolume = availableAmount - selectedFuelAmount;
		}
		tank2_GSC_Can_Read.Signal();
		tank2Semaphore.Signal();
		break;
	case 3:
		tank3Semaphore.Wait();
		availableAmount = tank3Ptr->currentFuelVolume;
		if (availableAmount > 200){
			tank3Ptr->currentFuelVolume = availableAmount - selectedFuelAmount;
		}
		tank3_GSC_Can_Read.Signal();
		tank3Semaphore.Signal();
		break;
	case 4:
		tank4Semaphore.Wait();
		availableAmount = tank4Ptr->currentFuelVolume;
		if (availableAmount > 200){
			tank4Ptr->currentFuelVolume = availableAmount - selectedFuelAmount;
		}
		tank4_GSC_Can_Read.Signal();
		tank4Semaphore.Signal();
		break;
	default:
		printf("invalid fuel selected\n");
		break;
	}
	return availableAmount;
}

//**************************************************************************************************************************************************
customerStatus c;	// Customer Being Served
pumpStatus ps;		// Current Status of Pump
Pump p;

//**************************************************************************************************************************************************
int main(){
	fuelTankStatus* tanksDatapoolPointers[4] = { tank1Ptr, tank2Ptr, tank3Ptr, tank4Ptr };
	printf("::::: PUMP 2 :::::\tWaiting on Rendezvous...\n");
	r1.Wait();
	system("cls");
	while (endSimulation.Read() == 0){

		//*********************************************************************************************************************************************
		// reset values
		c.customerName[0] = '\0';
		c.customerCC[0] = '\0';
		c.selectedFuel = 0;
		c.selectedFuelAmount = 0;

		ps.customerName[0] = 'N';
		ps.customerName[1] = '/';
		ps.customerName[2] = 'A';
		ps.customerName[3] = '\0';

		for (int i = 0; i < (MAX_CARD_LEN - 1); i++){
			ps.customerCC[i] = '0';
		}
		ps.customerCC[(MAX_CARD_LEN - 1)] = '\0';

		ps.priceToPay = 0;
		ps.selectedFuel = 0;
		ps.selectedFuelAmount = 0;
		ps.status = 0;

		// white on datapool for GSC
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();

		//*********************************************************************************************************************************************
		// check fuel amounts
		for (int i = 0; i < 4; i++){
			fuelTankStatus *tankPtr = tanksDatapoolPointers[i];

			p.setFuelPrice((i + 1), tankPtr->fuelPrice); // updates fuel price

			while (!(tankPtr->currentFuelVolume> 200)){
				screenSemaphore.Wait();
				TEXT_COLOUR(12);
				printf("::::: PUMP 2 :::::\tNot enough fuel on tank %d. Waiting for Refueling\n", (i + 1));
				SLEEP(5000);
				TEXT_COLOUR();
				screenSemaphore.Signal();
				SLEEP(5000);
			}
		}

		printf("::::: PUMP 2 :::::\tWaiting for another customer...\n");;
		//**************************************************************************************************************************************************
		//wait on producer Pipe semaphore
		prodPipe.Wait();

		//consume data from pipe1 (copy to object)
		Pipe_in.Read(&c, sizeof(customerStatus));

		//*****************************************************************************************************************************************
		// receive new customer
		// prompts that new customer have arrived
		screenSemaphore.Wait();
		std::cout << "::::: PUMP 2 :::::\t" << "Customer " << c.customerName << " arrived\n";
		screenSemaphore.Signal();

		//*****************************************************************************************************************************************
		// Write values in pumpStatus
		// name
		int nameSize = strlen(c.customerName);
		for (int i = 0; i < nameSize; i++){
			ps.customerName[i] = c.customerName[i];
		}
		//ps.customerName[nameSize] = '/0';

		// card
		for (int i = 0; i < (MAX_CARD_LEN - 1); i++){
			ps.customerCC[i] = c.customerCC[i];
		}
		//ps.customerCC[(MAX_CARD_LEN - 1)] = '/0';

		//*****************************************************************************************************************************************
		screenSemaphore.Wait();
		printf("::::: PUMP 2 :::::\tCustomer selecting fuel...\n");
		screenSemaphore.Signal();

		ps.status = 1;
		// white on datapool for GSC
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();

		SLEEP(2000);
		// get fuel type
		unsigned int selectedFuel = c.selectedFuel;
		p.setSelectedFuel(selectedFuel);
		screenSemaphore.Wait();
		printf("::::: PUMP 2 :::::\tCustomer selected fuel %d\n", selectedFuel);
		screenSemaphore.Signal();

		//*****************************************************************************************************************************************
		screenSemaphore.Wait();
		printf("::::: PUMP 2 :::::\tCustomer selecting fuel amount...\n");
		screenSemaphore.Signal();

		ps.status = 2;
		// white on datapool for GSC
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();

		SLEEP(2000);
		// get amount
		unsigned int selectedFuelAmount = c.selectedFuelAmount;
		p.setSelectedFuelAmount(selectedFuelAmount);
		screenSemaphore.Wait();
		printf("::::: PUMP 2 :::::\tCustomer selected fuel amount = %d\n", selectedFuelAmount);
		screenSemaphore.Signal();

		//*****************************************************************************************************************************************
		p.setPriceToPay();
		float priceToPay = p.getPriceToPay();

		//**************************************************************************************************************************************************
		// Update Pump Status
		ps.selectedFuel = selectedFuel;
		ps.selectedFuelAmount = selectedFuelAmount;
		ps.priceToPay = priceToPay;

		//**************************************************************************************************************************************************
		// comunicate with the GSC. Put Status on datapool;
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();

		//**************************************************************************************************************************************************
		// gets amount of fuel in selected tank
		unsigned int availableAmount = getTankFuelAmount(selectedFuel, selectedFuelAmount); //p1.getSelectedFuel());

		//*****************************************************************************************************************************************
		// receives payment
		screenSemaphore.Wait();
		std::cout << "::::: PUMP 2 :::::\t" << "Waiting for payment\n";
		screenSemaphore.Signal();

		ps.status = 5;
		// white on datapool for GSC
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();


		p.receivePayment();

		screenSemaphore.Wait();
		std::cout << "::::: PUMP 2 :::::\t" << "Paid\n";
		screenSemaphore.Signal();

		//*****************************************************************************************************************************************
		SLEEP(1000); // wait certain time to remove the hose

		screenSemaphore.Wait();
		std::cout << "::::: PUMP 2 :::::\t" << "Hose removed from pump\n";
		screenSemaphore.Signal();
		SLEEP(3000); // wait certain time to put the hose on the car

		screenSemaphore.Wait();
		std::cout << "::::: PUMP 2 :::::\t" << "Dispensing fuel\n";
		screenSemaphore.Signal();

		ps.status = 3;
		// white on datapool for GSC
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();

		p.fillCustomer(); // dispense fuel to car

		screenSemaphore.Wait();
		std::cout << "::::: PUMP 2 :::::\t" << "Hose returned to pump\n";
		screenSemaphore.Signal();

		ps.status = 4;
		// white on datapool for GSC
		consPool.Wait();
		*pumpStatusPtr = ps;
		prodPool.Signal();

		SLEEP(5000); //wait for the customer to go away

		//*******************************************************************************************************************************************
		// Pump is empty and can receive anoher customer
		screenSemaphore.Wait();
		cout << "::::: PUMP 2 :::::\t" << "Pump is free\n";
		screenSemaphore.Signal();

		//signal consumerPipe
		consPipe.Signal();
	}
	return 0;
}