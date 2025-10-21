#include <iostream>

using namespace std;

//This code will be teach me how to code a payrool system

//Function prototypes
void instruct_user(float tax_bracket, float tax);
float compute_gross(float hours, float rate, float overtime_rate, float max_hours);
float compute_net(float gross_pay, float tax_bracket, float tax);

int main() {


	const float tax_bracket = 100.0; //The amount that the user will get taxed at
	const float tax = tax_bracket * 0.25; //The amount that the user will get taxed
	const float max_hours = 40.0;
	const float overtime_rate = 2.0;

	//Variables
	float hours{};
	float rate;
	float gross_pay;
	float net_pay;

	//Instruct the user
	instruct_user(tax_bracket, tax);

	cout << "Enter the number of hours worked: ";
	cin >> hours;
	cout << "Enter the hourly rate: ";
	cin >> rate;

	if (hours > 40) {
		cout << "You have worked more than 40 hours, you get overtime pay!! " << endl;

	}
	else if (hours < 40 && hours >= 24) {
		cout << "Your worked the right amout this week, Thank you!" << endl;

	}
	else if (hours <= 23 && hours > 0) {
		cout << "Didn't work much this week, are you ok!" << endl;

	}
	else if (hours == 0){
		cout << "you haven't worked at all, please contact your manager. " << endl;
		return 0;
	}

	//Compute the gross pay
	gross_pay = compute_gross(hours, rate, overtime_rate, max_hours);

	//Compute the net pay
	net_pay = compute_net(gross_pay, tax_bracket, tax);

	//print out the results
	cout << "Gross Pay: $" << gross_pay << endl;
	cout << "Net Pay: $" << net_pay << endl;


}

void instruct_user(float tax_bracket, float tax) {
	//This function will instruct the user
	cout << "This program will compute your gross and net pay." << endl;
	cout << "If your gross pay is higher than $" << tax_bracket << ", you will be taxed $" << tax << "." << endl;
	cout << "Otherwise, you will not be taxed." << endl;
}

float compute_gross(float hours, float rate, float overtime_rate, float max_hours) {
	//This function will compute the gross pay

	if (hours <= max_hours) {
		return hours * rate;
	}
	else if (hours > max_hours) {
		return (overtime_rate * hours) * rate;
	}

	

}

float compute_net(float gross_pay, float tax_bracket, float tax) {
	//This function will compute the net pay
	
	//If the gross pay is higher than 100, then get taxed if not, then return the gross pay
	if (gross_pay > tax_bracket) { 
		return gross_pay - tax; // it is taking 25 % of 100 which is 25
	}
	else if (gross_pay < tax_bracket) {
		return gross_pay;
	}
	else if (gross_pay == tax_bracket){

		return gross_pay;
	}


}