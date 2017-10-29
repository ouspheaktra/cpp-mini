#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// find a number in array of int
bool find(int number, int array[], int size) {
	for (int i = 0; i < size; i++)
		if (number == *(array+i))
			return true;
	return false;
}

main() {
	srand(time(NULL));
	
	// ask to input size of array A and B
	int sizeA, sizeB;
	cout << "Input size of A : "; cin >> sizeA;
	cout << "Input size of B : "; cin >> sizeB;
	
	// random value and cout array A
	int arrA[sizeA];
	cout << "Array A :" << endl;
	for (int i = 0; i < sizeA; i++) {
		arrA[i] = rand()%10;
		cout << arrA[i] << " ";
	}
	
	// random value and cout array B
	int arrB[sizeB];
	cout << "\n\nArray B :" << endl;
	for (int i = 0; i < sizeB; i++) {
		arrB[i] = rand()%10;
		cout << arrB[i] << " ";
	}
	
	// generate an array to store A not in B
	int sizeMax = (sizeA > sizeB) ? sizeA : sizeB;
	int size = 0;
	int arrR[sizeMax];	// array result
	int *pA = arrA;
	int *pB = arrB;
	int *pR = arrR;
	for (int i = 0; i < sizeA; i++) {
		if (!find(*(pA+i), pB, sizeB) && !find(*(pA+i), pR, size))
			*(pR+size++) = *(pA+i);
	}
	for (int i = 0; i < sizeB; i++) {
		if (!find(*(pB+i), pA, sizeA) && !find(*(pB+i), pR, size))
			*(pR+size++) = *(pB+i);
	}
	
	cout << "\n\nA not common B :" << endl;
	for (int i = 0; i < size; i++)
		cout << arrR[i] << " ";
}
