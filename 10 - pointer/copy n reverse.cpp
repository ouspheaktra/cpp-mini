#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
void copyArray(int *parr1, int *parr2, int size) {
	for (int i = 0; i < size; i++)
		*(parr2+i) = *(parr1+i); 
}
void reverseArray(int *parr, int size) {
	for (int i = 0; i < size/2; i++) {
		int temp = *(parr+i);
		*(parr+i) = *(parr+size-1-i);
		*(parr+size-1-i) = temp;
	}
}
main() {
	srand(time(NULL));
	const short size = 10;
	int arr1[size];
	for (int i = 0; i < size; i++)	arr1[i] = rand()%10;
	
	int arr2[size];
	copyArray(arr1, arr2, size);
	reverseArray(arr2, size);
	
	for (int i = 0; i < size; i++) cout << arr1[i] << " ";
	cout << endl;
	for (int i = 0; i < size; i++) cout << arr2[i] << " ";
}
