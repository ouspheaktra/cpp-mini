/*
	There is a stack of pancakes of different radii.
	The only operation carried out with them - between any two pancakes we push a kitchen spatula and change an order of pancakes over the spatula to the reverse order.
	It is necessary to implement a minimum number of such operations to sort pancakes from down to up descending radius.
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;
int main() {
	// create array with random value and display it
	const int size = 100;
	srand(time(NULL));
	int array[size];
	for (int i = 0; i < size; i++) {
		array[i] = rand()%90 + 10;
		cout << array[i] << " ";
	}
	
	int time = 0;	// number of time of changing the order of pancake
	
	// improve bubble sort
	int done, i, j;
	for (i = 0; i < size; i++) {
		done = true;
		for (j = 0; j < size-1-i; j++) {
			if (array[j] > array[j+1]) {
				swap(array[j], array[j+1]);
				time++;
				done = false;
			}
		}
		if (done) break;
	}
	
	// display pancake after sorted
	cout << endl;
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
	
	// display number of time used
	cout << "Swap " << time << " times";
	
}
