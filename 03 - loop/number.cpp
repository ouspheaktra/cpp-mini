/*
	Number of Digits
	Sum of its Digits
	Arithmetic of its Digits
	Number of Zeros
*/
#include <iostream>
using namespace std;
main() {
	long number;
	int digit, sum, zero, option, exit;
	while (1) {
		
		// choose app
		cout << "Choose" << endl;
		cout << "1 - Number of digits" << endl;
		cout << "2 - Sum of its digits" << endl;
		cout << "3 - Arithmetic of its digits" << endl;
		cout << "4 - Number of zeros" << endl;
		cout << "5 - EXIT the application" << endl;
		cin >> option;
		
		// if out of option, next loop
		if (option < 1 || option > 5) {
			cout << "1 to 4, not " << option << endl << "---" << endl;
			continue;
		}
		
		// if exit, exit
		if (option == 5) break;
		
		// input number
		cout << "Input a number : "; cin >> number;
		
		// set everything to 0
		digit = sum = zero = 0;
		
		// loop to get everything
		for (long temp = number, dgt = 0; temp != 0; temp/=10) {
			digit++;
			dgt = temp % 10;
			if (dgt == 0) zero++;
			sum += dgt;
		}
		
		// according to the option, switch to view the result
		switch (option) {
			case 1: cout << "Number of digits : " << digit; break;
			case 2: cout << "The sum of its digits : " << sum; break;
			case 3: cout << "The arithmetic of its digits : " << (float)sum/digit; break;
			case 4: cout << "The number of zeros : " << zero; break;
		}
		cout << endl << "---" << endl;
	}
	cout << "GOODBYE";
}
