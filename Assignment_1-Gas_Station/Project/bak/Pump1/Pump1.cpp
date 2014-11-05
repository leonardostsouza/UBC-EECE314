////#include "..\Pump.h"
//#include "..\rt.h"
//#include "..\Customer.h"
//
//using namespace std;
//
//CRendezvous r1("MyRendezvous", 2);
//
//CSemaphore prodPipe1("pipe1Producer", 0, 1);
//CSemaphore consPipe1("pipe1Consumer", 1, 1);
//
//CSemaphore prodPool1("pool1Producer", 0, 1);
//CSemaphore consPool1("pool1Consumer", 1, 1);
//
//typedef struct pumpStatus{
//	string customerName;
//	string customerCC;		//Credit Card Numer
//	unsigned int fuelType;		// Fuel Chosen by the customer
//	unsigned int fuelAmount;	// amount of fuel being filled
//};
//
//typedef struct customerCar {
//	string name;
//	string card;
//	unsigned int fuelType;
//	unsigned int fuelAmount;
//};
//
////typedef struct pumpStatus{
////	char customerName[MAXIMUM_NAME_LEN];
////	char customerCC[CARD_NUMBER_LEN];		//Credit Card Numer
////	unsigned int fuelType;		// Fuel Chosen by the customer
////	unsigned int fuelAmount;	// amount of fuel being filled
////};
////
////typedef struct customerCar {
////	char name[MAXIMUM_NAME_LEN];
////	char card[CARD_NUMBER_LEN];
////	unsigned int fuelType;
////	unsigned int fuelAmount;
////};
//
//
//
int main(){
//
//	/*CSemaphore prodPipe1("pipe1Producer", 0, 1);
//	CSemaphore consPipe1("pipe1Consumer", 1, 1);*/
//
//
//	printf("\n\nPump1 arriving at rendezvous...\n");
//	r1.Wait(); //wait for rendezvous
//	printf("GO!!!\n");
//
//	// datapool from  pump to Gas Station Computer window
//	CDataPool pump1DP("Pump1", sizeof(pumpStatus));
//	pumpStatus *pump1Ptr = (pumpStatus *)(pump1DP.LinkDataPool());
//	printf("Pump linked to datapool at address %p.....\n", pump1Ptr);
//
//	// pipeline from customers to Pump
//	CPipe Pipe1_in("Pipe1_in", 2048);//sizeof(customerCar));
//	printf("pipe created\n");
//
//	//Pump p1(Pipe1_in, pump1Ptr, prodPipe1, consPipe1, prodPool1, consPool1);
//
//	//p1.WaitForThread();
//
//
//	printf("creating c\n");
//	customerCar c;			//customer being served
//	printf("c created\n");
//	// consume data from pipe
//	printf("P1 waiting\n");
//	prodPipe1.Wait();
//	
//	int size;
//	Pipe1_in.Read(&size, sizeof(int));
//
//	consPipe1.Signal();
//	prodPipe1.Wait();
//
//	Pipe1_in.Read(&c, size);//sizeof(c));
//	printf("read from pipe\n");
//	cout << "name = " << c.name << "\n";
//	//cout << "card = " << c.card << "\n";
//	cout << "fuel type = " << c.fuelType << "\n";
//	cout << "fuel amount = " << c.fuelAmount << "\n";
//	consPipe1.Signal();
//
//
//
//	// produce data to Datapool
//
//	consPool1.Wait();
//	printf("writing...\n");
//	// writing name
//	/*for (int i = 0; i < MAXIMUM_NAME_LEN; i++)
//		pump1Ptr->customerName[i] = c.name[i];*/
//	pump1Ptr->customerName = c.name;
//	cout << "name = " << pump1Ptr->customerName << "\n";
//	// writing card number
//	/*for (int i = 0; i < CARD_NUMBER_LEN; i++)
//		pump1Ptr->customerCC[i] = c.card[i];*/
//	//pump1Ptr->customerCC = c.card;
//	cout << "card = " << pump1Ptr->customerCC << "\n";
//	// writing fuelType
//	pump1Ptr->fuelType = c.fuelType;
//	cout << "fuel type = " << pump1Ptr->customerCC << "\n";
//	//printf("fuel type = %s\n", c.fuelType);
//	//printf("fuel type = %s\n", pump1Ptr->fuelType);
//	// writing fuelAmount
//	pump1Ptr->fuelAmount = c.fuelAmount;
//	cout << "fuel amount = " << pump1Ptr->customerCC << "\n";
//	//printf("fuel amount = %s\n", c.fuelAmount);
//	//printf("fuel amount (liters) = %s\n", pump1Ptr->fuelAmount);
//	printf("done\n");
//
//	prodPool1.Signal();
//
//
//	//customerCar c;			//customer being served
//
//	//// consume data from pipe
//	//prodPipe1.Wait();
//
//	//Pipe1_in.Read(&c, sizeof(c));
//	//printf("read from pipe\n");
//
//	//consPipe1.Signal();
//
//
//	//// produce data to Datapool
//	//consPool1.Wait();
//
//	//printf("writing...\n");
//	//// writing name
//	//for (int i = 0; i < MAXIMUM_NAME_LEN; i++)
//	//	pump1Ptr->customerName[i] = c.name[i];
//	//printf("name = %s\n", pump1Ptr->customerName);
//	//// writing card number
//	//for (int i = 0; i < CARD_NUMBER_LEN; i++)
//	//	pump1Ptr->customerCC[i] = c.card[i];
//	//printf("cc = %s\n", pump1Ptr->customerCC);
//	//// writing fuelType
//	////pump1Ptr->fuelType = c.fuelType;
//	////printf("fuel type = %s\n", c.fuelType);
//	////printf("fuel type = %s\n", pump1Ptr->fuelType);
//	//// writing fuelAmount
//	////pump1Ptr->fuelAmount = c.fuelAmount;
//	////printf("fuel amount = %s\n", c.fuelAmount);
//	////printf("fuel amount (liters) = %s\n", pump1Ptr->fuelAmount);
//	////printf("done\n");
//
//	//prodPool1.Signal();
//
//
//	system("pause");
//
	return 0;
}