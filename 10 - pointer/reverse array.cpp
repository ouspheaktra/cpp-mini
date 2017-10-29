#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
void reverseArray(int *parr, int size) {
	for (int i = 0; i < size/2; i++) {
		int temp = *(parr+i);
		*(parr+i) = *(parr+size-1-i);
		*(parr+size-1-i) = temp;
	}
}
main() {
	const short size = 10;
	int arr1[size];
	for (int i = 0; i < size; i++) {
		arr1[i] = rand()%10;
		cout << arr1[i] << " ";
	}
	
	reverseArray(arr1, size);
	
	cout << endl;
	for (int i = 0; i < size; i++) cout << arr1[i] << " ";

}
