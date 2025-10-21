#include <iostream>


using namespace std;

//Function to compute insurance division

//Function prototypes
void instruct_user_insurance(float basic_rate, float bonus_rate);
float compute_dividend(float premium, int number_claims, float basic_rate, float bonus_rate);

int main() {

	//Constants
	const float basic_rate = 0.045;
	const float bonus_rate = 0.005;

	//Variables
	float premium;
	int number_claims;
	float dividend;

	//Instruct the user
	instruct_user_insurance(basic_rate, bonus_rate);
	cout << "Enter your insurance premium amount: $";
	cin >> premium;
	cout << "Enter the number of claims made: ";
	cin >> number_claims;

	//Compute the dividend
	dividend = compute_dividend(premium, number_claims, basic_rate, bonus_rate);

	//Print out the results
	cout << "Your insurance dividend is: $" << dividend << endl;
	if (number_claims == 0) {
		cout << "You are eligible for the full dividend!" << endl;
	}

	return 0;


}

void instruct_user_insurance(float basic_rate, float bonus_rate) {
	cout << "This program will calculate your insurance premium based on the number of claims made." << endl;
	cout << "The Basic dividend is " << basic_rate << "times the premuim" << endl;
	cout << "A Bonus dividend of " << bonus_rate << " times the premium will be added for each claim made." << endl;
	cout << "For policies with no claims against them" << endl;
	return;
}

// Change the return type of compute_dividend to float and fix its logic
float compute_dividend(float premium, int number_claims, float basic_rate, float bonus_rate) {
	float dividend;

	dividend = premium * basic_rate;
	if (number_claims == 0) {
		dividend = dividend + premium * bonus_rate;

	}
	return dividend;
}
