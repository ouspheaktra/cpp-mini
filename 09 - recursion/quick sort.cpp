#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;

// cout array
void coutArray(int array[], int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}

// check if array is sorted
bool isSorted(int array[], int size) {
	for (int i = 0; i < size-1; i++)
		if (array[i] > array[i+1]) return false;
	return true;
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

main() {
	srand(time(NULL));
	const int size = 100;
	int array[size];
	for (int i = 0; i < size; i++) array[i] = rand()%90 + 10;
	coutArray(array, size);
	quickSort(array, size);
	coutArray(array, size);
	if (isSorted(array, size))
		cout << "It is sorted.";
	else
		cout << "It's not sorted.";
}
