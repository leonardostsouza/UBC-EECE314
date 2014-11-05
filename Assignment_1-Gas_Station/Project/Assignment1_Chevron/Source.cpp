#include "..\Pump.h"
#include "..\rt.h"
#include "..\Customer.h"
#include <iostream>
#include <stdio.h>
#include <queue>
#include <time.h>

#define FUEL_TYPE_TANK_CAPACITY 500

#define TOTAL_CUSTOMERS 30

#define WAIT_MIN 5 // in seconds
#define WAIT_MAX 30 // in seconds

using namespace std;

//**************************************************************************************************************************************************
// Control Semaphores
CSemaphore endSimulation("endSimulation", 0, 1);
//**************************************************************************************************************************************************
// Source Semaphores
CSemaphore customersWaitingSemaphore("customersWaitingSemaphore", 1, 1);
//**************************************************************************************************************************************************
// Screen Semaphores
CSemaphore screenSemaphore("screenSemaphore", 1, 1);
//**************************************************************************************************************************************************
//PUMP 1 semaphores
CSemaphore prodPipe1("pipe1Producer", 0, 1);
CSemaphore consPipe1("pipe1Consumer", 1, 1);

CSemaphore prodPool1("pool1Producer", 0, 1);
CSemaphore consPool1("pool1Consumer", 1, 1);
//**************************************************************************************************************************************************
//PUMP 2 semaphores
CSemaphore prodPipe2("pipe2Producer", 0, 1);
CSemaphore consPipe2("pipe2Consumer", 1, 1);

CSemaphore prodPool2("pool2Producer", 0, 1);
CSemaphore consPool2("pool2Consumer", 1, 1);
//**************************************************************************************************************************************************
//PUMP 3 semaphores
CSemaphore prodPipe3("pipe3Producer", 0, 1);
CSemaphore consPipe3("pipe3Consumer", 1, 1);

CSemaphore prodPool3("pool3Producer", 0, 1);
CSemaphore consPool3("pool3Consumer", 1, 1);
//**************************************************************************************************************************************************
//PUMP 4 semaphores
CSemaphore prodPipe4("pipe4Producer", 0, 1);
CSemaphore consPipe4("pipe4Consumer", 1, 1);

CSemaphore prodPool4("pool4Producer", 0, 1);
CSemaphore consPool4("pool4Consumer", 1, 1);
//**************************************************************************************************************************************************
// pipelines from customers to pumps
CPipe Pipe1_in("Pipe1_in", PUMP_PIPE_SIZE);
CPipe Pipe2_in("Pipe2_in", PUMP_PIPE_SIZE);
CPipe Pipe3_in("Pipe3_in", PUMP_PIPE_SIZE);
CPipe Pipe4_in("Pipe4_in", PUMP_PIPE_SIZE);
//**************************************************************************************************************************************************
queue<Customer> customersWaiting;

//Ads Customers in the queue, while they wait for an available pump
class CustomerArrival : public ActiveClass{
	void includeCustomer(){
		Customer c;
		customersWaiting.push(c);
	}
	long unsigned int setWaitTime(){
		long unsigned int wait_time;

		random_device rd;
		wait_time = WAIT_MIN + (rd() % WAIT_MAX); // min = WAIT_MIN; MAX = WAIT_MIN + WAIT_MAX
		wait_time = wait_time * 1000;

		return wait_time;
	}
public:
	int main(){
		for (int i = 0; i < TOTAL_CUSTOMERS; i++){
			includeCustomer();
			screenSemaphore.Wait();
			printf("\nNew Customer Arrived...\n\n");
			screenSemaphore.Signal();
			SLEEP(setWaitTime());	//Wait for random time before inserting new customer in queue
		}
		return 0;
	}
};
//**************************************************************************************************************************************************
// customers going to pumps
Customer c1;
Customer c2;
Customer c3;
Customer c4;

customerStatus c1_s;
customerStatus c2_s;
customerStatus c3_s;
customerStatus c4_s;


int main(){
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

	// Writing on Fuel Tank Datapools
	std::printf("Inicializing fuel tanks...\n");
	tank1Ptr->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	tank2Ptr->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	tank3Ptr->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	tank4Ptr->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;

	tank1Ptr->fuelPrice = FUEL_BASE_PRICE;
	tank2Ptr->fuelPrice = FUEL_BASE_PRICE + 0.2;
	tank3Ptr->fuelPrice = FUEL_BASE_PRICE + 0.4;
	tank4Ptr->fuelPrice = FUEL_BASE_PRICE + 0.6;
	std::printf("Done...\n");

//**************************************************************************************************************************************************
	// Creating the Pumps processes
	CProcess pump1("Pump1.exe",	// PUMP 1				
		NORMAL_PRIORITY_CLASS,			
		PARENT_WINDOW,	// OWN_WINDOW,//								
		SUSPENDED							
		);
	CProcess pump2("Pump2.exe",	// PUMP 2				
		NORMAL_PRIORITY_CLASS,			
		PARENT_WINDOW,										
		SUSPENDED							
		);
	CProcess pump3("Pump3.exe",	// PUMP 3				
		NORMAL_PRIORITY_CLASS,			
		PARENT_WINDOW,										
		SUSPENDED							
		);
	CProcess pump4("Pump4.exe",	// PUMP 4				
		NORMAL_PRIORITY_CLASS,			
		PARENT_WINDOW,										
		SUSPENDED							
		);
	CProcess GSC("GSC.exe",	// Gas Station Computer				
		NORMAL_PRIORITY_CLASS,			
		OWN_WINDOW,//PARENT_WINDOW,										
		SUSPENDED	
		);
//**************************************************************************************************************************************************
	pump1.Resume();
	pump2.Resume();
	pump3.Resume();
	pump4.Resume();
	GSC.Resume();
//**************************************************************************************************************************************************
	// includes customers in queue
	CustomerArrival arrivingCustomers;
	arrivingCustomers.Resume();
//**************************************************************************************************************************************************
//put people from queue to pipes of pumps
	while (endSimulation.Read() == 0){
		if (!customersWaiting.empty()){
			//pump 1
			if (consPipe1.Read() > 0){
				consPipe1.Wait(); // wait for PUMP 1 process to signal consumer semaphore

				customersWaitingSemaphore.Wait();
				c1.copy(customersWaiting.front()); // copies values from the first customer in line
				customersWaiting.pop(); // delete customer from queue
				customersWaitingSemaphore.Signal();

				// get name
				unsigned int customerNameSize = c1.getName().size();

				for (int i = 0; i < customerNameSize; i++){
					c1_s.customerName[i] = c1.getName().at(i);
				}
				c1_s.customerName[customerNameSize] = '\0';

				// get card
				for (int i = 0; i < (MAX_CARD_LEN - 1); i++){
					c1_s.customerCC[i] = c1.getCardNumber().at(i);
				}
				c1_s.customerCC[(MAX_CARD_LEN - 1)] = '\0';

				// select fuel
				c1_s.selectedFuel = c1.selectFuel();

				// select amount of fuel
				c1_s.selectedFuelAmount = c1.selectFuelAmount();

				//Write in pipeline
				Pipe1_in.Write(&c1_s, sizeof(customerStatus)); // writes the copies object to pipe

				screenSemaphore.Wait();
				std::cout << "\nCustomer " << c1_s.customerName << " gone to Pump 1...\n\n";
				screenSemaphore.Signal();

				prodPipe1.Signal(); // signal the producer semaphore to wake up PUMP 1
			}
		}

		if (!customersWaiting.empty()){
			//pump 2
			if (consPipe2.Read() > 0){
				consPipe2.Wait(); // wait for PUMP 2 process to signal consumer semaphore

				customersWaitingSemaphore.Wait();
				c2.copy(customersWaiting.front()); // copies values from the first customer in line
				customersWaiting.pop(); // delete customer from queue
				customersWaitingSemaphore.Signal();

				// get name
				unsigned int customerNameSize = c2.getName().size();

				for (int i = 0; i < customerNameSize; i++){
					c2_s.customerName[i] = c2.getName().at(i);
				}
				c2_s.customerName[customerNameSize] = '\0';

				// get card
				for (int i = 0; i < (MAX_CARD_LEN - 1); i++){
					c2_s.customerCC[i] = c2.getCardNumber().at(i);
				}
				c2_s.customerCC[(MAX_CARD_LEN - 1)] = '\0';

				// select fuel
				c2_s.selectedFuel = c2.selectFuel();

				// select amount of fuel
				c2_s.selectedFuelAmount = c2.selectFuelAmount();

				//Write in pipeline
				Pipe2_in.Write(&c2_s, sizeof(customerStatus)); // writes the copies object to pipe

				screenSemaphore.Wait();
				std::cout << "\nCustomer " << c2_s.customerName << " gone to Pump 2...\n\n";
				screenSemaphore.Signal();

				prodPipe2.Signal(); // signal the producer semaphore to wake up PUMP 2
			}
		}

		if (!customersWaiting.empty()){
			//pump 3
			if (consPipe3.Read() > 0){
				consPipe3.Wait(); // wait for PUMP 3 process to signal consumer semaphore

				customersWaitingSemaphore.Wait();
				c3.copy(customersWaiting.front()); // copies values from the first customer in line
				customersWaiting.pop(); // delete customer from queue
				customersWaitingSemaphore.Signal();

				// get name
				unsigned int customerNameSize = c3.getName().size();

				for (int i = 0; i < customerNameSize; i++){
					c3_s.customerName[i] = c3.getName().at(i);
				}
				c3_s.customerName[customerNameSize] = '\0';

				// get card
				for (int i = 0; i < (MAX_CARD_LEN - 1); i++){
					c3_s.customerCC[i] = c3.getCardNumber().at(i);
				}
				c3_s.customerCC[(MAX_CARD_LEN - 1)] = '\0';

				// select fuel
				c3_s.selectedFuel = c3.selectFuel();

				// select amount of fuel
				c3_s.selectedFuelAmount = c3.selectFuelAmount();

				//Write in pipeline
				Pipe3_in.Write(&c3_s, sizeof(customerStatus)); // writes the copies object to pipe

				screenSemaphore.Wait();
				std::cout << "\nCustomer " << c3_s.customerName << " gone to Pump 3...\n\n";
				screenSemaphore.Signal();

				prodPipe3.Signal(); // signal the producer semaphore to wake up PUMP 3
			}
		}
		if (!customersWaiting.empty()){
			//pump 4
			if (consPipe4.Read() > 0){
				consPipe4.Wait(); // wait for PUMP 4 process to signal consumer semaphore

				customersWaitingSemaphore.Wait();
				c4.copy(customersWaiting.front()); // copies values from the first customer in line
				customersWaiting.pop(); // delete customer from queue
				customersWaitingSemaphore.Signal();

				// get name
				unsigned int customerNameSize = c4.getName().size();

				for (int i = 0; i < customerNameSize; i++){
					c4_s.customerName[i] = c4.getName().at(i);
				}
				c4_s.customerName[customerNameSize] = '\0';

				// get card
				for (int i = 0; i < (MAX_CARD_LEN - 1); i++){
					c4_s.customerCC[i] = c4.getCardNumber().at(i);
				}
				c4_s.customerCC[(MAX_CARD_LEN - 1)] = '\0';

				// select fuel
				c4_s.selectedFuel = c4.selectFuel();

				// select amount of fuel
				c4_s.selectedFuelAmount = c4.selectFuelAmount();

				//Write in pipeline
				Pipe4_in.Write(&c4_s, sizeof(customerStatus)); // writes the copies object to pipe

				screenSemaphore.Wait();
				std::cout << "\nCustomer " << c4_s.customerName << " gone to Pump 4...\n\n";
				screenSemaphore.Signal();

				prodPipe4.Signal(); // signal the producer semaphore to wake up PUMP 4
			}
		}
	}
//**************************************************************************************************************************************************
	pump1.~CProcess();
	pump2.~CProcess();
	pump3.~CProcess();
	pump4.~CProcess();
	arrivingCustomers.~CustomerArrival();
	GSC.WaitForProcess();
//**************************************************************************************************************************************************
	return 0;
}