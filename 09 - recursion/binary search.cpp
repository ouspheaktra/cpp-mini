#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;

void coutArray(int array[], int size);		// cout id:number
void quickSort(int array[], int size);
int binarySearch(int number, int array[], int size);

main() {
	srand(time(NULL));
	const int size = 10;
	int array[size];
	for (int i = 0; i < size; i++) array[i] = rand()%9;
	coutArray(array, size);
	quickSort(array, size);
	cout << endl;
	coutArray(array, size);
	cout << binarySearch(5, array, size);
}

// return -1 means not found
// return 0 to ... means the position of found number
int binarySearch(int number, int array[], int size) {
	if (size == 1)
		if (array[0] == number)	return 0;
		else					return -1;
		
	int middle = size/2;
	int found;
	if (number == array[middle])	return middle;
	if (number < array[middle])		return binarySearch(number, array, middle);
	else {
		found = binarySearch(number, array+middle, size-middle);
		if (found == -1)	return -1;
		else				return found + middle;
	}
	return -1;
}

// cout array
void coutArray(int array[], int size) {
	for (int i = 0; i < size; i++)
		cout << i << ":" << array[i] << " ";
	cout << endl;
}

// quick sort
void quickSort(int array[], int size) {
	// partitioning (pivot is the most left)
	int pivot = 0;
	int bigger = 0;
	for (int i = 1; i < size; i++) {
		// if current number is greater than a number at the pivot
		if (array[i] > array[pivot]) {
			// swap the greater number to the last
			swap(array[i], array[size-1-bigger]);
			bigger++;
			i--;
		}
		// if hit the greater number, break
		if (i == size-1-bigger) break;
	}
	// swap the pivot to the last of smaller number
	swap(array[pivot], array[size-1-bigger]);
	pivot = size-1-bigger;
	// if the left side have more than one element, quick sort the left side
	if (pivot > 1)
		quickSort(array, pivot);
	// if the right side have more that one element, quick sor the right side
	if (size-pivot-1 > 1)
		quickSort(array+pivot+1, size-pivot-1);
}
