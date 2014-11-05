#include "..\rt.h"
#include "..\Pump.h"

#define FUEL_TYPE_TANK_CAPACITY 500

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
//*******************************************************************************************************************
CSemaphore endSimulation("endSimulation", 0, 1);

//*******************************************************************************************************************
// DataPools for Fuel Tanks
CDataPool tank1DP("Tank1", sizeof(unsigned int));
CDataPool tank2DP("Tank2", sizeof(unsigned int));
CDataPool tank3DP("Tank3", sizeof(unsigned int));
CDataPool tank4DP("Tank4", sizeof(unsigned int));

fuelTankStatus *tank1Ptr = (fuelTankStatus *)(tank1DP.LinkDataPool());
fuelTankStatus *tank2Ptr = (fuelTankStatus *)(tank2DP.LinkDataPool());
fuelTankStatus *tank3Ptr = (fuelTankStatus *)(tank3DP.LinkDataPool());
fuelTankStatus *tank4Ptr = (fuelTankStatus *)(tank4DP.LinkDataPool());

//*******************************************************************************************************************

fuelTankStatus* tanksDatapoolPointers[4] = { tank1Ptr, tank2Ptr, tank3Ptr, tank4Ptr };
//*******************************************************************************************************************

void refillTank(int tank){
	fuelTankStatus *tankPtr;
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
	if (tankPtr != NULL){
		cout << "Waiting for fuel truck\n";
		SLEEP(10000);
		cout << "Truck arrived. Refilling tank " << tank << " at 10 l/s...\n";
		UINT refillTime = (FUEL_TYPE_TANK_CAPACITY - (tankPtr->currentFuelVolume)) * 100;
		SLEEP(refillTime);
		tankPtr->currentFuelVolume = FUEL_TYPE_TANK_CAPACITY;
	}
	
}

void setFuelPrice(int fuel, float price){
	fuelTankStatus* tankPtr = tanksDatapoolPointers[(fuel - 1)];
	tankPtr->fuelPrice = price;
}

int main(){


	//*******************************************************************************************************************
	CProcess simulator("Assignment1_Chevron.exe",	// The Simulator			
		NORMAL_PRIORITY_CLASS,
		OWN_WINDOW,							
		SUSPENDED
		);

	//*******************************************************************************************************************
	

	cout << "Welcome to the:\n\n";

	TEXT_COLOUR(BLUE);
	cout << "   ______              _____ __        __  _           \n"
		<< "  / ____/___ ______   / ___// /_____ _/ /_(_)___  ____ \n"
		<< " / / __/ __ \'/ ___/   \\__ \\/ __/ __ \'/ __/ / __ \\/ __ \\\n"
		<< "/ /_/ / /_/ (__  )   ___/ / /_/ /_/ / /_/ / /_/ / / / /\n"
		<< "\\____/\\__,_/____/   /____/\\__/\\__,_/\\__/_/\\____/_/ /_/ \n";

	TEXT_COLOUR(RED);
	cout << "   _____ _                 __      __                  \n"
		<< "  / ___/(_)___ ___  __  __/ /___ _/ /_____  _____      \n"
		<< "  \\__ \\/ / __ `__ \\/ / / / / __ `/ __/ __ \\/ ___/      \n"
		<< " ___/ / / / / / / / /_/ / / /_/ / /_/ /_/ / /          \n"
		<< "/____/_/_/ /_/ /_/\\__,_/_/\\__,_/\\__/\\____/_/           \n";
	TEXT_COLOUR();
	cout << "\nDesigned and Programmed by:\n\tLeonardo dos Santos Teixeira de Souza\n\tStudent Number: 56410146"
		<< "\n\nThe University British Columbia\nEECE 314 - System Software Engineering\nWINTER SESSION 2014\nASSIGNMENT 1\n\n";
	cout << "====================\nType \"help\" to list valid commands\nType \"start\" to start simulation\n====================\n\n";
	string command;
	bool command_valid;

	while (command != "stop"){
		command = "null";
		cout << "manager@GasStation:~$ ";
		cin >> command;
		command_valid = false;

		if (command == "help"){
			// list commands
			cout << "\nhelp:\tlist this help\nstart:\tstart simulation\nstop:\tend simulation\n"
				<< "clear:\tclear screen\n\nprintFuelPrices:\tprints the current fuel prices\nsetFuelPrice:\t\tchanges the price of a fuel\n"
				<< "refillTank:\t\trefills a selected tank\n\n";
			command_valid = true;
		}

		if (command == "start"){
			simulator.Resume();
			cout << "Simulator Started!\n\n";
			command_valid = true;
		}

		if (command == "stop"){
			cout << "Stopping simulation... This may take a few minutes...\n";
			if (endSimulation.Read() == 0){
				endSimulation.Signal();
			}
			command_valid = true;
		}

		if (command == "clear"){
			system("cls");
			command_valid = true;
		}

		if (command == "printFuelPrices"){
			cout << "Fuel 1: CAD$ " << tank1Ptr->fuelPrice << " per liter\n"
				<< "Fuel 2: CAD$ " << tank2Ptr->fuelPrice << " per liter\n"
				<< "Fuel 3: CAD$ " << tank3Ptr->fuelPrice << " per liter\n"
				<< "Fuel 4: CAD$ " << tank4Ptr->fuelPrice << " per liter\n";
			command_valid = true;
		}

		if (command == "setFuelPrice"){
			int fuelType = 0;
			float fuelPrice;

			while (fuelType < 1 || fuelType>4){
				cout << "Of which fuel would you like to change price? ";
				cin >> fuelType;
				if (fuelType < 1 || fuelType>4){
					cout << "Invalid fuel type. Try again.\n";
				}
			}

			cout << "How much per liter is it going to be now?  CAD$";
			cin >> fuelPrice;

			setFuelPrice(fuelType, fuelPrice);

			cout << "Price changed.\n\n";
			command_valid = true;
		}

		if (command == "refillTank"){
			int tank = 0;

			while (tank < 1 || tank>4){
				cout << "Which tank would you like to refill? ";
				cin >> tank;
				if (tank < 1 || tank>4){
					cout << "Invalid tank. Try again.\n";
				}
			}

			refillTank(tank);

			cout << "Tank Refilled.\n\n";
			command_valid = true;
		}


		if (!command_valid && command != "null"){
			cout << "Command invalid.\n Type \"help\" for a list of valid commands\n\n";
		}
	}

	simulator.~CProcess();

	cout << "\n\nSIMULATION ENDED\n\n";

	system("pause");

	return 0;
}