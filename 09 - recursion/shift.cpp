#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;

const int size = 5;
int array[size][size];

void coutArray();
void shiftRight(int step);
void shiftLeft(int step);
void shiftUp(int step);
void shiftDown(int step);

main() {
	srand(time(NULL));
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			array[r][c] = rand()%10;

	coutArray();
	
	shiftRight(3);
	cout << "After shift right 3 :\n";
	coutArray();
	
	shiftLeft(2);
	cout << "After shift left 2 :\n";
	coutArray();
	
	shiftUp(7);
	cout << "After shift up 7 :\n";
	coutArray();
	
	shiftDown(3);
	cout << "After shift down 3 :\n";
	coutArray();
}

void shiftRight(int step) {
	if (step != 1)
		shiftRight(step-1);
	for (int r = 0; r < size; r++)
		for (int c = size-1; c > 0; c--)
			swap(array[r][c], array[r][c-1]);
}

void shiftLeft(int step) {
	if (step != 1)
		shiftLeft(step-1);
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size-1; c++)
			swap(array[r][c], array[r][c+1]);
}

void shiftUp(int step) {
	if (step != 1)
		shiftUp(step-1);
	for (int c = 0; c < size; c++)
		for (int r = 0; r < size-1; r++)
			swap(array[r][c], array[r+1][c]);
}

void shiftDown(int step) {
	if (step != 1)
		shiftDown(step-1);
	for (int c = 0; c < size; c++)
		for (int r = size-1; r > 0; r--)
			swap(array[r][c], array[r-1][c]);
}

void coutArray() {
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++)
			cout << array[r][c] << " ";
		cout << endl;
	}
	cout << endl;
}
