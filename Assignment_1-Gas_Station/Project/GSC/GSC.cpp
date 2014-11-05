#include "..\rt.h"
#include "..\Pump.h"
#include <time.h>
#include <fstream>

#define MIN_FUEL_AMOUNT 200
#define FLASH_SPEED 1000

#define BLACK		 0 
#define DARK_BLUE	 1
#define DARK_GREEN	 2
#define DARK_CYAN	 3
#define DARK_RED	 4
#define DARK_MAGENTA 5
#define DARK_YELLOW	 6
#define DARK_GRAY	 7
#define BLACK_2		 8
#define BLUE		 9
#define GREEN		 10
#define CYAN		 11
#define RED			 12
#define MAGENTA		 13
#define YELLOW		 14
#define WHITE		 15
 
using namespace std;
//**************************************************************************************************************************************************
// Control Semaphores
CSemaphore endSimulation("endSimulation", 0, 1);

//**************************************************************************************************************************************************
CRendezvous r1("MyRendezvous", 5);

//**************************************************************************************************************************************************
CSemaphore GSCLogFileSemaphore("GSCLogFileSemaphore", 1, 1);

//**************************************************************************************************************************************************
CSemaphore prodPool1("pool1Producer", 0, 1);
CSemaphore consPool1("pool1Consumer", 1, 1);

CSemaphore prodPool2("pool2Producer", 0, 1);
CSemaphore consPool2("pool2Consumer", 1, 1);

CSemaphore prodPool3("pool3Producer", 0, 1);
CSemaphore consPool3("pool3Consumer", 1, 1);

CSemaphore prodPool4("pool4Producer", 0, 1);
CSemaphore consPool4("pool4Consumer", 1, 1);

//**************************************************************************************************************************************************
CSemaphore tank1_GSC_Can_Read("tank1_GSC_Can_Read", 0, 1);
CSemaphore tank2_GSC_Can_Read("tank2_GSC_Can_Read", 0, 1);
CSemaphore tank3_GSC_Can_Read("tank3_GSC_Can_Read", 0, 1);
CSemaphore tank4_GSC_Can_Read("tank4_GSC_Can_Read", 0, 1);

//**************************************************************************************************************************************************
// datapools from each pump to Gas Station Computer window
CDataPool pump1DP("Pump1", sizeof(pumpStatus));
CDataPool pump2DP("Pump2", sizeof(pumpStatus));
CDataPool pump3DP("Pump3", sizeof(pumpStatus));
CDataPool pump4DP("Pump4", sizeof(pumpStatus));

pumpStatus *pump1Ptr = (pumpStatus *)(pump1DP.LinkDataPool());
pumpStatus *pump2Ptr = (pumpStatus *)(pump2DP.LinkDataPool());
pumpStatus *pump3Ptr = (pumpStatus *)(pump3DP.LinkDataPool());
pumpStatus *pump4Ptr = (pumpStatus *)(pump4DP.LinkDataPool());

//**************************************************************************************************************************************************
CDataPool tank1DP("Tank1", sizeof(unsigned int));
CDataPool tank2DP("Tank2", sizeof(unsigned int));
CDataPool tank3DP("Tank3", sizeof(unsigned int));
CDataPool tank4DP("Tank4", sizeof(unsigned int));

unsigned int *tank1Ptr = (unsigned int *)(tank1DP.LinkDataPool());
unsigned int *tank2Ptr = (unsigned int *)(tank2DP.LinkDataPool());
unsigned int *tank3Ptr = (unsigned int *)(tank3DP.LinkDataPool());
unsigned int *tank4Ptr = (unsigned int *)(tank4DP.LinkDataPool());

//**************************************************************************************************************************************************
ofstream log_file;

//**************************************************************************************************************************************************
void printTime(){
	time_t t = time(0);   // get time now
	tm now;
	localtime_s(&now, &t);
	if (log_file.is_open()){
		log_file	<< "\n========== TIME : " << (now.tm_year + 1900) << "-" << (now.tm_mon + 1) << '-'
					<< now.tm_mday << " at " << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << " ==========\n";
	}
}

void printTimeScreen(){
	time_t t = time(0);   // get time now
	tm now;
	localtime_s(&now, &t);
	cout	<< "\n========== TIME : " << (now.tm_year + 1900) << "-" << (now.tm_mon + 1) << '-'
			<< now.tm_mday << " at " << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << " ==========\n";
}

//**************************************************************************************************************************************************
class printPumpStatus : public ActiveClass {
	unsigned int pump;
public:
	printPumpStatus(unsigned int _pump){
		pump = _pump;
	}

	int main(){
		switch (pump){
		case 1:
			while (endSimulation.Read() == 0){
				prodPool1.Wait();
				GSCLogFileSemaphore.Wait();
				if (log_file.is_open()){
					printTime();
					log_file	<< "******************\nPUMP 1:\nCustomer Name = " << pump1Ptr->customerName
								<< "\nCredit Card = " << pump1Ptr->customerCC
								<< "\nFuel Type = " << pump1Ptr->selectedFuel
								<< "\nFuel Amount = " << pump1Ptr->selectedFuelAmount
								<< " liters\nTotal Price = CAD$" << pump1Ptr->priceToPay
								<< "\n\n";
				}
				GSCLogFileSemaphore.Signal();
				consPool1.Signal();
			}
				break;
			
		case 2:
			while (endSimulation.Read() == 0){
				prodPool2.Wait();
				GSCLogFileSemaphore.Wait();
				if (log_file.is_open()){
					printTime();
					log_file << "******************\nPUMP 2:\nCustomer Name = " << pump2Ptr->customerName
							 << "\nCredit Card = " << pump2Ptr->customerCC
							 << "\nFuel Type = " << pump2Ptr->selectedFuel
							 << "\nFuel Amount = " << pump2Ptr->selectedFuelAmount
							 << " liters\nTotal Price = CAD$" << pump2Ptr->priceToPay
							 << "\n\n";
				}
				GSCLogFileSemaphore.Signal();
				consPool2.Signal();
			}
				break;
			
		case 3:
			while (endSimulation.Read() == 0){
				prodPool3.Wait();
				GSCLogFileSemaphore.Wait();
				if (log_file.is_open()){
					printTime();
					log_file << "******************\nPUMP 3:\nCustomer Name = " << pump3Ptr->customerName
							 << "\nCredit Card = " << pump3Ptr->customerCC
							 << "\nFuel Type = " << pump3Ptr->selectedFuel
							 << "\nFuel Amount = " << pump3Ptr->selectedFuelAmount
							 << " liters\nTotal Price = CAD$" << pump3Ptr->priceToPay
							 << "\n\n";
				}
				GSCLogFileSemaphore.Signal();
				consPool3.Signal();
			}
			break;
		case 4:
			while (endSimulation.Read() == 0){
				prodPool4.Wait();
				GSCLogFileSemaphore.Wait();
				if (log_file.is_open()){
					printTime();
					log_file << "******************\nPUMP 4:\nCustomer Name = " << pump4Ptr->customerName
							 << "\nCredit Card = " << pump4Ptr->customerCC
							 << "\nFuel Type = " << pump4Ptr->selectedFuel
							 << "\nFuel Amount = " << pump4Ptr->selectedFuelAmount
							 << " liters\nTotal Price = CAD$" << pump4Ptr->priceToPay
							 << "\n\n";
				}
				GSCLogFileSemaphore.Signal();
				consPool4.Signal();
			}
			break;
		default:
			printf("infalid pump\n");
			break;
		}
		return 0;
	}
};

//**************************************************************************************************************************************************
class printFuelTankStatus : public ActiveClass{
	unsigned int tank;
	unsigned int * tankPtr;
public:
	printFuelTankStatus(unsigned int _tank, unsigned int *_tankPtr){ tank = _tank; tankPtr = _tankPtr; }

	int main(){
		while (endSimulation.Read() == 0){
			switch (tank){
			case 1:
				tank1_GSC_Can_Read.Wait();
				break;
			case 2: 
				tank2_GSC_Can_Read.Wait();
				break;
			case 3:
				tank3_GSC_Can_Read.Wait();
				break;
			case 4:
				tank4_GSC_Can_Read.Wait();
				break;
			}
			
			unsigned int fuelAmount = *tankPtr;

			if (fuelAmount > 200){
				GSCLogFileSemaphore.Wait();
				printTime();
				log_file << "******************\nTANK " << tank << ":\nAvailable amount (liters) = " << fuelAmount << "\n\n";
				GSCLogFileSemaphore.Signal();
			}
			else {
				GSCLogFileSemaphore.Wait();
				printTime();
				log_file << "******************\n";
				log_file << "WARNING!!!\nTANK " << tank
					<< ":\nAvailable amount (liters) = " << fuelAmount
					<< "\nWARNING!!!" << "\n\n";
				GSCLogFileSemaphore.Signal();
			}
		}
		return 0;
	}
};

//**************************************************************************************************************************************************
void printGSCScreen(){
	while (endSimulation.Read() == 0){
		system("cls");
		cout << "REAL TIME STATUS:";
		printTimeScreen();
		// pumps
		for (int pump = 1; pump < 5; pump++){
			pumpStatus *pumpPtr;

			switch (pump){
			case 1:
				pumpPtr = pump1Ptr;
				break;
			case 2:
				pumpPtr = pump2Ptr;
				break;
			case 3:
				pumpPtr = pump3Ptr;
				break;
			case 4:
				pumpPtr = pump4Ptr;
				break;
			default:
				pumpPtr = NULL;
				break;
			}

			cout << "******************\nPUMP " << pump << ":\nCustomer Name = " << pumpPtr->customerName
				<< "\nCredit Card = " << pumpPtr->customerCC
				<< "\nFuel Type = " << pumpPtr->selectedFuel
				<< "\nFuel Amount = " << pumpPtr->selectedFuelAmount
				<< " liters\nTotal Price = CAD$" << pumpPtr->priceToPay
				<< "\n";

			switch (pumpPtr->status){
			case 0:
				TEXT_COLOUR(GREEN);
				cout << "PUMP FREE\n\n";
				TEXT_COLOUR();
				break;
			case 1:
				TEXT_COLOUR(YELLOW);
				cout << "CUSTOMER SELECTING FUEL\n\n";
				TEXT_COLOUR();
				break;
			case 2:
				TEXT_COLOUR(DARK_YELLOW);
				cout << "CUSTOMER SELECTING FUEL AMOUNT\n\n";
				TEXT_COLOUR();
				break;
			case 3:
				TEXT_COLOUR(CYAN);
				cout << "DISPENSING FUEL\n\n";
				TEXT_COLOUR();
				break;
			case 4:
				TEXT_COLOUR(MAGENTA);
				cout << "WAITING FOR CUSTOMER TO GO AWAY\n\n";
				TEXT_COLOUR();
				break;
			case 5:
				TEXT_COLOUR(BLUE);
				cout << "WAITING FOR PAIMENT\n\n";
				TEXT_COLOUR();
				break;
			default:
				pumpPtr = NULL;
				break;
			}
		}
		// tanks
		for (int tank = 1; tank < 5; tank++) {
			unsigned int *tankPtr;

			switch (tank){
			case 1:
				tankPtr = tank1Ptr;
				break;
			case 2:
				tankPtr = tank2Ptr;
				break;
			case 3:
				tankPtr = tank3Ptr;
				break;
			case 4:
				tankPtr = tank4Ptr;
				break;
			default:
				tankPtr = NULL;
				break;
			}

			unsigned int fuelAmount = *tankPtr;

			if (fuelAmount > 200){
				cout << "******************\nTANK " << tank << ":\nAvailable amount (liters) = " << fuelAmount << "\n\n";
			}
			else {
				cout << "******************\n";
				TEXT_COLOUR(RED);
				cout << "WARNING!!!\nTANK " << tank
					<< ":\nAvailable amount (liters) = " << fuelAmount
					<< "\nWARNING!!!" << "\n\n";
				TEXT_COLOUR();
			}
		}

		SLEEP(FLASH_SPEED);
	}
}

//**************************************************************************************************************************************************
printPumpStatus p1(1);
printPumpStatus p2(2);
printPumpStatus p3(3);
printPumpStatus p4(4);

printFuelTankStatus t1(1, tank1Ptr);
printFuelTankStatus t2(2, tank2Ptr);
printFuelTankStatus t3(3, tank3Ptr);
printFuelTankStatus t4(4, tank4Ptr);

int main(){
	printf("GSC arriving at rendezvous...\n");
	r1.Wait();

	log_file.open("..\\log_file.txt", ios::out | ios::app);

	p1.Resume();
	p2.Resume();
	p3.Resume();
	p4.Resume();

	t1.Resume();
	t2.Resume();
	t3.Resume();
	t4.Resume();

	printGSCScreen();

	p1.~printPumpStatus();
	p2.~printPumpStatus();
	p3.~printPumpStatus();
	p4.~printPumpStatus();

	t1.~printFuelTankStatus();
	t2.~printFuelTankStatus();
	t3.~printFuelTankStatus();
	t4.~printFuelTankStatus();

	log_file.close();

	return 0;
}