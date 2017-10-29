/*
	Shift 2d Array
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
main() {
	cout << "Here is the ORIGINAL ARRAY" << endl << endl;
	
	const int size = 6;
	int array[size][size];
	srand(time(NULL));
	
	// Display original array
	//int a = 10;	// for testing only
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			array[r][c] = rand()%90 + 10;
			//array[r][c] = a++;	// for testing only
			cout << array[r][c] << " ";
		}
		cout << endl;
	}
	
	// ask for direction
	int direction;
	cout << endl;
	cout << "1 : Left" << endl;
	cout << "2 : Right" << endl;
	cout << "3 : Up" << endl;
	cout << "4 : Down" << endl;
	cout <<"Which direction do you want to shift? "; cin >> direction;
	if (direction < 1 || direction > 4) {
		cout << "1 2 3 or 4, not " << direction << endl;
		return 1;
	}
	
	// ask for step to shift
	int step;
	cout << endl << "How many steps do you want to shift? "; cin >> step;
	if (step < 0) {
		cout << "The amount of steps cannot be NEGATIVE."<< endl;
		return 2;
	}
	step %= size;
	
	// shift the array
	cout << endl;
	int shifted[size][size];
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			int row = r;	// row, use in original array
			int col = c;	// col, use in original array
			switch (direction) {
				case 1:	// to LEFT
					if (c+step > size-1)	col = c+step - size;
					else					col = c+step;
					break;
				case 2:	// to RIGHT
					if (c-step < 0)	col = size + c-step;
					else 			col = c-step;
					break;
				case 3:	// to UP
					if (r+step > size-1)	row = r+step - size;
					else					row = r+step;
					break;
				case 4: // to DOWN
					if (r-step < 0)	row = size + r-step;
					else			row = r-step;
					break;
			}
			shifted[r][c] = array[row][col];
			cout << shifted[r][c] << " ";
		}
		cout << endl;
	}
}
