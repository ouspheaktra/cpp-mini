/*
	Display the number of digits of a number
	and The sum of its digits
*/

#include <iostream>
using namespace std;
main() {
	int number;
	
	// ask user to input a number
	cout << "Please input a number : "; cin >> number;
	
	// if it is not between 0 and 100
	if (number >= 100 || number <= 0) {
		cout << "The number has to be between 0 and 100.";

	// if it is a valid number
	} else {

		// if it's one-digit
		if (number < 10) {
			cout << number << " has 1 digit.\n";
			cout << "This sum of the digit is " << number;

		// if it's two digits
		} else {
			cout << number << " has 2 digits.\n";
			cout << "This sum of the digits is " << number / 10 + number % 10;
		}
	}
}
