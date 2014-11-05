//#include "..\Pump.h"
#include "..\rt.h"
#include "..\Customer.h"
#include <iostream>

#define FUEL_TYPE_TANK_CAPACITY 500
#define PUMP_PIPE_SIZE 1024

using namespace std;

//RENDEZVOUS
CRendezvous rdv("MyRendezvous", 2);

// PUMP 1 SEMAPHORES
CSemaphore prodPipe1("pipe1Producer", 0, 1); // MAIN to PUMP 1 (via Pipe 1)
CSemaphore consPipe1("pipe1Consumer", 1, 1); 

CSemaphore prodPool1("pool1Producer", 0, 1); // PUMP 1 to GSC (via Pool 1)
CSemaphore consPool1("pool1Consumer", 1, 1);

// STATUS
typedef struct pumpStatus{
	string customerName;
	string customerCC;		//Credit Card Numer
	unsigned int fuelType;		// Fuel Chosen by the customer
	unsigned int fuelAmount;	// amount of fuel being filled
};

// CUSTOMER CAR
typedef struct customerCar {
	string name;
	string card;
	unsigned int fuelType;
	unsigned int fuelAmount;
};

//PUMP ACTIVE CLASS
class Pump : public ActiveClass {
public:
	Pump(CPipe _pipe, pumpStatus* _poolPtr, CSemaphore _producerPipe, CSemaphore _consumerPipe, CSemaphore _producerPool, CSemaphore _consumerPool){
		pipe = &_pipe;
		poolPtr = _poolPtr;

		producerPipe = &_producerPipe;
		producerPipe = &_consumerPipe;
		producerPool = &_producerPool;
		consumerPool = &_consumerPool;
	}

	//~Pump(){}

	//bool isPaid();			// checks if the Pump has already received payment

	//void receiveCustomer(Customer *);	// receives next Customer on the queue 
	////void makePaiment(Customer *);
	//void fillCustomer();			// fills the Customer with fuel

	int main(){

		printf("\n\nPump1 arriving at rendezvous...\n");
		rdv.Wait(); //wait for rendezvous
		printf("GO!!!\n");

		// datapool from  pump to Gas Station Computer window
		printf("Pump linked to datapool at address %p.....\n", poolPtr);

		printf("creating c\n");
		customerCar c;			//customer being served
		printf("c created\n");
		// consume data from pipe
		printf("P1 waiting\n");

		//producerPipe->Wait();
		printf("end waiting\n");
		pipe->Read(&c, sizeof(c));
		printf("read from pipe\n");
		cout << "name = " << c.name << "\n";
		//cout << "card = " << c.card << "\n";
		cout << "fuel type = " << c.fuelType << "\n";
		cout << "fuel amount = " << c.fuelAmount << "\n";
		consumerPipe->Signal();



		// produce data to Datapool

		consumerPool->Wait();
		printf("writing...\n");
		// writing name
		poolPtr->customerName = c.name;
		cout << "name = " << poolPtr->customerName << "\n";

		// writing card number
		//pump1Ptr->customerCC = c.card;
		cout << "card = " << poolPtr->customerCC << "\n";

		// writing fuelType
		poolPtr->fuelType = c.fuelType;
		cout << "fuel type = " << poolPtr->customerCC << "\n";

		//writing fuelAmount
		poolPtr->fuelAmount = c.fuelAmount;
		cout << "fuel amount = " << poolPtr->customerCC << "\n";

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
//END PUMP ACTIVE CLASS


typedef struct fuelTankStatus{
	unsigned int currentFuelVolume;
};

int main(){

	// datapools of pumps status
	CDataPool pump1DP("Pump1", sizeof(pumpStatus));
	//CDataPool pump2DP("Pump2", sizeof(pumpStatus));
	//CDataPool pump3DP("Pump3", sizeof(pumpStatus));
	//CDataPool pump4DP("Pump4", sizeof(pumpStatus));

	pumpStatus *pump1Ptr = (pumpStatus *)(pump1DP.LinkDataPool());
	//pumpStatus *pump2Pt = (pumpStatus *)(pump2DP.LinkDataPool());
	//pumpStatus *pump3Pt = (pumpStatus *)(pump3DP.LinkDataPool());
	//pumpStatus *pump4Pt = (pumpStatus *)(pump4DP.LinkDataPool());

	// pipelines from customers to pumps
	CPipe Pipe1_in("Pipe1_in", 2048);// sizeof(customerCar));
	/*CPipe Pipe2_in("Pipe2_in", PUMP_PIPE_SIZE);
	CPipe Pipe3_in("Pipe3_in", PUMP_PIPE_SIZE);
	CPipe Pipe4_in("Pipe4_in", PUMP_PIPE_SIZE);*/

	// pipelines for each pump to Gas Station Computer window
	//CPipe Pipe1_out("Pipe1_out", PUMP_PIPE_SIZE);
	//CPipe Pipe2_out("Pipe2_out", PUMP_PIPE_SIZE);
	//CPipe Pipe3_out("Pipe3_out", PUMP_PIPE_SIZE);
	//CPipe Pipe4_out("Pipe4_out", PUMP_PIPE_SIZE);

	// DataPools for Fuel Tanks
	CDataPool tank1DP("Tank1", sizeof(fuelTankStatus));
	CDataPool tank2DP("Tank2", sizeof(fuelTankStatus));
	CDataPool tank3DP("Tank3", sizeof(fuelTankStatus));
	CDataPool tank4DP("Tank4", sizeof(fuelTankStatus));

	fuelTankStatus *tank1Pt = (fuelTankStatus *)(tank1DP.LinkDataPool());
	fuelTankStatus *tank2Pt = (fuelTankStatus *)(tank2DP.LinkDataPool());
	fuelTankStatus *tank3Pt = (fuelTankStatus *)(tank3DP.LinkDataPool());
	fuelTankStatus *tank4Pt = (fuelTankStatus *)(tank4DP.LinkDataPool());

	// Writing on Fuel Tank Datapools
	printf("Inicializing fuel tanks...\n");
	tank1Pt->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	tank2Pt->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	tank3Pt->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	tank4Pt->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	
	// Creating the Pumps treads

	Pump pump1(Pipe1_in, pump1Ptr, prodPipe1, consPipe1, prodPool1, consPool1);
	//Pump pump2(Pipe2_in, pump2Ptr, prodPipe2, consPipe2, prodPool2, consPool2);
	//Pump pump3(Pipe3_in, pump3Ptr, prodPipe3, consPipe3, prodPool3, consPool3);
	//Pump pump4(Pipe4_in, pump4Ptr, prodPipe4, consPipe4, prodPool4, consPool4);

	pump1.Resume();

	
	CProcess GSC("C:\\Users\\Leonardo\\Desktop\\UBC\\EECE314\\Assignments\\1\\Assignment1_Chevron\\Debug\\GSC.exe",	// Gas Station Computer				
		NORMAL_PRIORITY_CLASS,			
		OWN_WINDOW,									
		ACTIVE	
		);



	// *********************************************************************************************
	// *************************************** TEST CODE *******************************************
	// *********************************************************************************************

	printf("reading values from Fuel Tanks datapools...\n");
	unsigned int i = tank1Pt->currentFuelVolume;
	printf("amount for tank 1 = %d\n", i);
	i = tank2Pt->currentFuelVolume;
	printf("amount for tank 2 = %d\n", i);
	i = tank3Pt->currentFuelVolume;
	printf("amount for tank 3 = %d\n", i);
	i = tank4Pt->currentFuelVolume;
	printf("amount for tank 4 = %d\n", i);

	consPipe1.Wait(); // producer - consumer pipe 1

	printf("writing in CUSTOMER - PUMP pipes... \n\n");
	// create a customer to Pump
	Customer c1;
	customerCar c1_s;
	// get curtomer's name
	
	c1_s.name = c1.getName();
	cout << "Wrote name = " << c1_s.name << " on struct 1\n" ;
	/*for (int i = 0; i < MAXIMUM_NAME_LEN; i++){
		c1_s.name[i] = c1.getName()[i];
		printf("%c", c1_s.name[i]);
	}*/

	// get Customer's Credit Card

	c1_s.card = c1.getCardNumber();
	cout << "Wrote card = " << c1_s.card << " on struct 1\n";
	//cout << "Wrote card = " << c1.getCardNumber() << " on struct 1\n";
	//for (int i = 0; i < CARD_NUMBER_LEN; i++)
	//	c1_s.card[i] = c1.getCardNumber()[i];
	//printf("name = %s\n", c1_s.name);
	//printf("card = %s\n", c1_s.card);
	// get customer's fuel type and amount
	c1_s.fuelType = c1.selectFuel();
	printf("fueltype = %d\n", c1_s.fuelType);
	c1_s.fuelAmount = c1.selectFuelQuantity();
	printf("fuelamount = %d\n", c1_s.fuelAmount);
	// put everything insite pipe

	consPipe1.Wait();

	Pipe1_in.Write(&c1_s, sizeof(c1_s));//size);// sizeof(c1_s));//sizeof(c1_s));
	//Customer c2;
	//Pipe2_in.Write(&c2, sizeof(c2));
	//Customer c3;
	//Pipe2_in.Write(&c3, sizeof(c2));
	//Customer c4;
	//Pipe2_in.Write(&c4, sizeof(c2));
	printf("DONE \n");

	//prodPipe1.Signal(); // producer - consumer pipe 1

	// *********************************************************************************************
	// *************************************** TEST CODE *******************************************
	// *********************************************************************************************

	//pump1.Resume();
	//pump2.Resume();
	//pump3.Resume();
	//pump4.Resume();
	//SLEEP(1000);
	//GSC.Resume();

	pump1.WaitForThread();
	//pump2.WaitForProcess();
	//pump3.WaitForProcess();
	//pump4.WaitForProcess();
	GSC.WaitForProcess();

	printf("simulation ended\n");

#ifdef _WIN32 || _WIN64
	system("pause");
#endif
	return 0;
}