/*
	Write a program that implements the sum of elements of two arrays separately and the results are recorded in third array.
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
main() {
	srand(time(NULL));
	
	const int size = 5;
	int arr_1[size];
	int arr_2[size];
	int sum[size];
	
	for (int i = 0; i < size; i++) {
		
		// random for array 1
		arr_1[i] = rand() % 100;
		
		// random for array 2
		arr_2[i] = rand() % 100;
		
		// sum array 1 and 2
		sum[i] = arr_1[i] + arr_2[i];
	}
	
	cout << "Array 1 : \t";
	for (int i = 0; i < size; i++)	cout << arr_1[i] << " ";
	
	cout << endl << "Array 2 : \t";
	for (int i = 0; i < size; i++)	cout << arr_2[i] << " ";
	
	cout << endl << "Sum : \t\t";
	for (int i = 0; i < size; i++)	cout << sum[i] << " ";
}
