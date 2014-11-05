#include "Customer.h"

Customer::Customer(){
	setName();
	setCardNumber();
}

Customer::~Customer(){}

void Customer::copy(Customer c){
	name = c.getName();
	cardNumber = c.getCardNumber();
}

unsigned int Customer::selectFuel(){
	std::random_device rd;
	int fuel = 1 + (rd() % DIFFERENT_FUEL_TYPES);
	return fuel;
}

unsigned int Customer::selectFuelAmount(){
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
	string names[] = { "Anna", "Bernard", "Chris", "Charles", "Diego", "Emma", "Ferdinand", "George", "Homer", "Irina", "Jill", "Kelly", "Leon", "Michael", "Natasha", "Oscar", "Peter", "Quirinus", "Roger", "Sergei", "Thomas", "Ursula", "Victor", "Wesker", "Xena", "Yoshi", "Zelda"};
	string surnames[] = { "Almund", "Balkan", "Corleone", "Dorca", "Erwin", "Fawkes", "Gear", "Hail", "Ivanovich", "Jackson", "Korolev", "Lombardi", "Moore", "Nash", "Orwell", "Parker", "Qadir", "Redfield", "Simpson" "Trovalds", "Utterson", "Valentine", "Wilde", "Xavier", "Yvarolev", "Zidane"};

	std::random_device rd;

	int nameInt = rd() % 27;		// 27 is the number of elements in names[]
	int surnameInt = rd() % 26;		// 26 is the number of elements in surnames[]

	string firstName = names[nameInt];
	string lastName = surnames[surnameInt];
	const string space = " ";

	name = firstName + space + lastName;
}

void Customer::setCardNumber(){ 
	std::random_device rd;
	string temp = "5";
	for (int i = 1; i < CARD_NUMBER_LEN; i++){
		int number = rd() % 10;
		temp = temp + to_string(number);
	}
	cardNumber = temp;
}