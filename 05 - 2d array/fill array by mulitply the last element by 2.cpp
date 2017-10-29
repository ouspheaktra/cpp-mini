/*
	Write a program that creates two-dimensional array and fills it in the following way:
		the user enters a number (for example, 3)
		the first element of the array takes a value of this number,
		the subsequent element of the array takes a value of this number multiplied by 2 (that is 6 for our example),
		the third element of the array takes a value of the previous element, multiplied by 2 (that is 6 * 2 = 12 in our example).
		Display an array that has been created.
*/
#include <iostream>
using namespace std;
main() {
	long number;
	cout << "Input a number : "; cin >> number;
	
	const int size = 4;
	long array[size][size];
	
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			array[r][c] = number;
			cout << array[r][c] << "\t";
			number *= 2;
		}
		cout << endl;
	}
}
