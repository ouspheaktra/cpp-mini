/*
	Write a program that copies sequentially elements of one array of 10 elements in 2 arrays each of which has 5 elements.
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
main() {
	srand(time(NULL));
	
	const int size = 10;
	int arr[size];
	int copy_1[size/2];
	int copy_2[size/2];
	
	for (int i = 0, half = size/2; i < size; i++) {
		
		// random
		arr[i] = rand() % 100;
		
		// if first half, copy to copy_1
		if (i < half)	copy_1[i] = arr[i];
		
		//if last half, copy to copy_2
		else			copy_2[i - half] = arr[i];
	}
	
	cout << "Original Array : \t";
	for (int i = 0; i < size; i++)	cout << arr[i] << " ";
	
	cout << endl << "Copy First Half : \t";
	for (int i = 0; i < size/2; i++)	cout << copy_1[i] << " ";
	
	cout << endl << "Copy Last Half : \t";
	for (int i = 0; i < size/2; i++)	cout << copy_2[i] << " ";
}
