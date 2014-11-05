#include "Customer.h"

Customer::Customer(){
	main();
}

Customer::~Customer(){}

unsigned int Customer::selectFuel(){
	std::random_device rd;
	int fuel = 1 + (rd() % DIFFERENT_FUEL_TYPES);
	return fuel;
}

unsigned int Customer::selectFuelQuantity(){
	std::random_device rd;
	int qtt = FUEL_MINIMUM_AMOUNT + (rd() % (CAR_FUEL_CAPACITY - FUEL_MINIMUM_AMOUNT));
	return qtt;
}

bool Customer::makePayment(){
	SLEEP(10000);	// time for the driver to take the card from his wallet
	return true;
}

string Customer::getName(){
	return name;
}

string Customer::getCardNumber(){
	return cardNumber;
}


void Customer::setName(){
	string names[] = { "Anna", "Bernard", "Charlie", "Diego", "Emma", "Ferdinand", "George", "Hanna", "Irina", "John", "Kelly", "Lucas", "Michael", "Natasha" };
	string surnames[] = { "Almund", "Balkan", "Corleone", "Dorca", "Erwin", "Fawkes", "Gear", "Hail", "Ivanovich", "Jackson", "Korolev", "Lombardi", "Moore", "Nash" };

	
	/*char* names[] = { "Anna", "Bernard", "Charlie", "Diego", "Emma", "Ferdinand", "George", "Hanna", "Irina", "John", "Kelly", "Lucas", "Michael", "Natasha" };
	char* surnames[] = { "Almund", "Balkan", "Corleone", "Dorca", "Erwin", "Fawkes", "Gear", "Hail", "Ivanovich", "Jackson", "Korolev", "Lombardi", "Moore", "Nash" };*/

	std::random_device rd;

	int nameInt = rd() % 14;		// 14 is the number of elements in names[]
	int surnameInt = rd() % 14;		// 14 is the number of elements in surnames[]

	string firstName = names[nameInt];
	string lastName = surnames[surnameInt];
	string space = " ";

	name = firstName + space + lastName;

	//int fullNameLen = strlen(names[nameInt]) + strlen(" ") + strlen(surnames[surnameInt]) + 1;
	/*int i = 0;*/
	
	//for (i = 0; i < strlen(names[nameInt]); i++){
	//	name[i] = names[nameInt][i];
	//}
	//name[i] = ' ';
	//i++;
	//for (int j = 0; j < strlen(names[nameInt]); j++){
	//	name[i + j] = surnames[surnameInt][j];
	//}
}

void Customer::setCardNumber(){ 
	std::random_device rd;
	cardNumber.resize(CARD_NUMBER_LEN);

	for (int i = 1; i < CARD_NUMBER_LEN; i++){ // cardNumber.size(); i++){
		cardNumber[i] = '0' + (rd() % 10);//'0' + (rd() % 10); // converts int to char
	}

	std::cout << "card = " << cardNumber << "\n";
}

int Customer::main(){
	setName();
	setCardNumber();
	return 0;
}