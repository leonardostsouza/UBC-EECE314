#include "..\rt.h"
#include "..\Customer.h"
//#include "..\Pump.h"

using namespace std;

CRendezvous rdv("MyRendezvous", 2);

CSemaphore prodPool1("pool1Producer", 0, 1);
CSemaphore consPool1("pool1Consumer", 1, 1);

typedef struct pumpStatus{
	string customerName;
	string customerCC;		//Credit Card Numer
	unsigned int fuelType;		// Fuel Chosen by the customer
	unsigned int fuelAmount;	// amount of fuel being filled
};

typedef struct customerCar {
	string name;
	string card;
	unsigned int fuelType;
	unsigned int fuelAmount;
};


//typedef struct pumpStatus{
//	char customerName[MAXIMUM_NAME_LEN];
//	char customerCC[CARD_NUMBER_LEN];		//Credit Card Numer
//	unsigned int fuelType;		// Fuel Chosen by the customer
//	unsigned int fuelAmount;	// amount of fuel being filled
//};

//ATTENTION! MODIFY CLASS FOR UNING ANY OTHER SEMAPHORE, NOT ONLY POOL 1!!! 
class GSCConsumerThread : public ActiveClass{
	pumpStatus *pumpPtr;
	int myId;
public:
	GSCConsumerThread(int id, pumpStatus *_pumpPtr){ myId = id;  pumpPtr = _pumpPtr;}
	~GSCConsumerThread(){}

	int main(){
		while (1){
			printf("waiting...\n");
			prodPool1.Wait();
			printf("reading...\n");

			cout << "******************\nPUMP " << myId << "\nCustomer Name = " << pumpPtr->customerName << "\nCredit Card = " << pumpPtr->customerCC
				<< "\nFuel Type = " << pumpPtr->fuelType << "\nFuel Amount = " << pumpPtr->fuelAmount << "\n\n";
			consPool1.Signal();
			system("cls");
		}
	}
};

int main(){

	printf("GSC arriving at rendezvous...\n");
	rdv.Wait();
	printf("GO!!!\n");
	// datapools from each pump to Gas Station Computer window
	CDataPool pump1DP("Pump1", sizeof(pumpStatus));
	//CDataPool pump2DP("Pump2", sizeof(pumpStatus));
	//CDataPool pump3DP("Pump3", sizeof(pumpStatus));
	//CDataPool pump4DP("Pump4", sizeof(pumpStatus));

	pumpStatus *pump1Pt = (pumpStatus *)(pump1DP.LinkDataPool());
	//pumpStatus *pump2Pt = (pumpStatus *)(pump2DP.LinkDataPool());
	//pumpStatus *pump3Pt = (pumpStatus *)(pump3DP.LinkDataPool());
	//pumpStatus *pump4Pt = (pumpStatus *)(pump4DP.LinkDataPool());
	printf("GSC linked to datapool at address %p.....\n", pump1Pt);

	// all of this should be in a thread

	// read from datapool and store values
	GSCConsumerThread PUMP1(1, pump1Pt);
	PUMP1.Resume();

	//while (1){
	//	// read from datapool and store values
	//	CustomerName = pump1Pt->customerName;
	//	CustomerCard = pump1Pt->customerCC;
	//	fuelType = pump1Pt->fuelType;
	//	fuelAmount = pump1Pt->fuelAmount;

	//	printf("GSC linked to datapool at address %p.....\n", pump1Pt);
	//	// read pump status
	//	printf("******************\nPUMP 1:\nCustomer Name = %s\nCredit Card = %s\nFuel Type = %d\nFuel Amount = %d\n\n",
	//		CustomerName,
	//		CustomerCard,
	//		fuelType,
	//		fuelAmount);

	//	//printf("******************\nPUMP 2:\nCustomer Name = %s\nCredit Card = %c\nFuel Type = %d\nFuel Amount = %d\n\n",
	//	//	pump2Pt->customerName,
	//	//	pump2Pt->customerCC,
	//	//	pump2Pt->fuelType,
	//	//	pump2Pt->fuelAmount);

	//	//printf("******************\nPUMP 3:\nCustomer Name = %s\nCredit Card = %c\nFuel Type = %d\nFuel Amount = %d\n\n",
	//	//	pump3Pt->customerName,
	//	//	pump3Pt->customerCC,
	//	//	pump3Pt->fuelType,
	//	//	pump3Pt->fuelAmount);

	//	//printf("******************\nPUMP 4:\nCustomer Name = %s\nCredit Card = %c\nFuel Type = %d\nFuel Amount = %d\n\n",
	//	//	pump4Pt->customerName,
	//	//	pump4Pt->customerCC,
	//	//	pump4Pt->fuelType,
	//	//	pump4Pt->fuelAmount);

	//	SLEEP(500);
	//	system("cls");
	//}
	PUMP1.WaitForThread();

	return 0;
}