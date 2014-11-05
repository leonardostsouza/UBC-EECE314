#include "..\Pump.h"
#include "..\rt.h"

#define PUMP_PIPE_SIZE 1024

using namespace std;

//typedef struct pumpStatus{
//	string customerName;
//	string customerCC;		//Credit Card Numer
//	unsigned int fuelType;		// Fuel Chosen by the customer
//	unsigned int fuelAmount;	// amount of fuel being filled
//};

//Customer c;
//
int main(){
	//
	//	//Pump p1;	// this pump
	//
	//	// datapool from  pump to Gas Station Computer window
	//	CDataPool pump3DP("Pump3", sizeof(pumpStatus));
	//	pumpStatus *pump3Pt = (pumpStatus *)(pump3DP.LinkDataPool());
	//
	//	// pipeline from customers to Pump
	//	CPipe Pipe3_in("Pipe3_in", PUMP_PIPE_SIZE);
	//
	//	pumpStatus status; // status to be written to Datapool
	//
	//	Pipe3_in.Read(&c, sizeof(c));
	//
	//	// get iformation from customer
	//	status.customerName = c.getName();
	//	status.customerCC = c.getCardNumber();
	//	status.fuelType = c.selectFuel();
	//	status.fuelAmount = c.selectFuelQuantity();
	//
	//	// write values in the datapool to GSM
	//	pump3Pt->customerName;
	//	pump3Pt->customerCC;
	//	pump3Pt->fuelType;
	//	pump3Pt->fuelAmount;
	//
	//	system("pause");
	//
	return 0;
}