#include <iostream>
using namespace std;

void selection_sort(int array[], int size);
void bubble_sort(int array[], int size);
void insertion_sort(int arra[], int size);
void reverse(int array[], int size);	// reverse array

main () {
	const int size = 7;
	int arr[size] = {12, 18, 2, 4, 3, 7, 9};
	bubble_sort(arr, size);
	reverse(arr, size);
	for (int i = 0; i < size; i++)
		cout << arr[i] << endl;
}
void reverse(int array[], int size) {
	int temp;
	for (int i = 0; i < size/2; i++) {
		temp = array[i];
		array[i] = array[size-1-i];
		array[size-1-i] = temp;
	}
}
void bubble_sort(int array[], int size) {
	int done, i, j;
	for (i = size-1; i > 0; i--) {
		done = true;
		for (j = 0; j < i; j++) {
			if (array[j] > array[j+1]) {
				int temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				done = false;
			}
		}
		if (done) break;
	}
}
void selection_sort(int array[], int size) {
	int min, minId, i, j;
	for (i = 0; i < size; i++) {
		min = array[i];
		minId = i;
		for (j = i+1; j < size; j++) {
			if (min > array[j])	{
				min = array[j];
				minId = j;
			}
		}
		array[minId] = array[i];
		array[i] = min;
	}
}
void insertion_sort(int arra[], int size) {
	
}
