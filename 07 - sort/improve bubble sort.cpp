/*
	Improve Bubble Sort
	Bubble-Selection Hybrid Sort
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;

void bubble_sort(int array[], int size);
void bubble_selection_sort(int array[], int size);	// BUBBLE + SELECTION sort

int main() {
	srand(time(NULL));
	
	// array with random value, display it
	const short size = 10;
	int array[size];
	for (int i = 0; i < size; i++) {
		array[i] = rand()%90 + 10;
		cout << array[i] << " ";
	}
	cout << endl << endl;
	
	// sort using bubble algorithm
	bubble_sort(array, size);
	
	// display the array after sorted
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
}

void bubble_sort(int array[], int size) {
	int done, i, j;
	for (i = size-1; i > 0; i--) {
		done = true;
		for (j = 0; j < i; j++) {
			if (array[j] > array[j+1]) {
				swap(array[j], array[j+1]);
				done = false;
			}
		}
		if (done) break;
	}
}

void bubble_selection_sort(int array[], int size) {
	int done, i, j, min, minId;
	for (i = 0; i < size; i++) {
		done = true;
		min = array[i];	// for selection sort
		minId = i;		// for selection sort
		for (j = i; j < size-1-i; j++) {
			
			// for bubble sort
			if (array[j] > array[j+1]) {
				swap(array[j], array[j+1]);
				done = false;
			}
			
			// for selection sort
			if (min > array[j]) {
				min = array[j];
				minId = j;
			}
		}
		if (done) break;
		swap(array[i], array[minId]);	// for selection sort
	}
}
