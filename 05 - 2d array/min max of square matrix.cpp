/* min n max of a part of 2d array */

#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
main() {
	// loop until the user provides a valid size
	int size;	// number of rows and cols
	while (1)	{
		cout << "Input size of array : "; cin >> size;
		if (size >= 3) break;
		else cout << "Size should not be smaller than 2" << endl << "---" << endl;
	}
	
	
	// loop until the user provides a valid option
	char option;
	while (1)	{
		cout << "Input one character from a to j : "; cin >> option;
		if (option >= 'a' && option <= 'j') break;
		else cout << "a to j, not " << option << endl << "---" << endl;
	}
	
	int array[size][size];
	srand(time(NULL));
	
	// generate random number (from 10 to 99) for all elements
	// and cout
	cout << "\nOriginal Number :" << endl;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			array[row][col] = rand()%90 + 10;
			cout << array[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	/* loop each element to find max */
	int max, start, end;
	bool first = true;
	cout << "Find Maximum number only in" << endl;
	// loop each row
	for (int row = 0; row < size; row++) {
		
		// different option, different start and end
		switch (option) {
			case 'a':
				start = row;
				end = size-1;
				break;
			case 'b':
				start = 0;
				end = row;
				break;
			case 'c':
				start = row;
				end = size-1-row;
				break;
			case 'd':
				start = size-1-row;
				end = row;
				break;
			case 'e':
				start = (row < size/2 ? row : size-1-row);
				end = (row < size/2 ? size-row-1 : row);
				break;
			case 'f':
				start = 0;
				end = size-1;	
				break;	
			case 'g':
				start = 0;
				end = (row < size/2 ? row : size-1-row);
				break;
			case 'h':
				start = (row < size/2 ? size-1-row : row);
				end = size-1;
				break;
			case 'i':
				start = 0;
				end = size-1-row;
				break;
			case 'j':
				start = size-1-row;
				end = size-1;
				break;
		}
		
		// cout spaces
		for (int col = 0; col < start; col++) cout << "   ";
		
		// loop each column
		for (int col = start; col <= end; col++) {
			
			// ONLY for option 'f'
			if (option == 'f')
				if ((row <= size/2) ? (col > row && col < size-row-1) : (col < row && col > size-row-1)) {
					cout << "   ";
					continue;
				}
					
			// find maximum
			if (first || max < array[row][col])
				max = array[row][col];
			
			cout << array[row][col] << " ";
			
			first = false;
		}
		cout << endl;
	}	
	cout << endl;
	
	cout << "MAX : " << max;
}
