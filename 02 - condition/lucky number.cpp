/*
    Is it a Lucky Number?
    A 6-digits Lucky Number : sum of the first 3-digits number == the sum of the last 3-digits number
*/

#include <iostream>
using namespace std;
main() {

    // ask for a 6-digits number
	int number;
	cout << "Please input a 6-digits number : ";
	cin >> number;

    // if it's NOT a 6-digits number
	if (number < 100000 || number >= 1000000) {
		cout << number << " is NOT a 6-digits number.";

    // if it's a 6-digits number
	} else {

        // each digit, from right to left
		int n1 = number%10;
		int n2 = number/10%10;
		int n3 = number/100%10;
		int n4 = number/1000%10;
		int n5 = number/10000%10;
		int n6 = number/100000;

        // if it's a lucky number
		if (n1+n2+n3 == n4+n5+n6)
			cout << number << " is a lucky number.";
        
        // if it's NOT a lucky number
		else
			cout << number << " is NOT a luck number.";
	}
}
