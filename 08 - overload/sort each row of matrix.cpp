/* 
	minimum and maximum of main diagnoal of matrix
	sort matrix each row separately
*/

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
using namespace std;
const short size = 5;

// minimum on the main diagonal of matrix of INT
int min_diagonal(int array[size][size]) {
	int min = array[0][0];
	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i == j && min > array[i][j])
				min = array[i][j];
	return min;
}

// minimum on the main diagonal of matrix of CHAR
char min_diagonal(char array[size][size]) {
	char min = array[0][0];
	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i == j && min > array[i][j])
				min = array[i][j];
	return min;
}

// minimum on the main diagonal of matrix of DOUBLE
double min_diagonal(double array[size][size]) {
	double min = array[0][0];
	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i == j && min > array[i][j])
				min = array[i][j];
	return min;
}

// maximum on the main diagonal of matrix of INT
int max_diagonal(int array[size][size]) {
	int max = array[0][0];
	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i == j && max < array[i][j])
				max = array[i][j];
	return max;
}

// maximum on the main diagonal of matrix of CHAR
char max_diagonal(char array[size][size]) {
	char max = array[0][0];
	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i == j && max < array[i][j])
				max = array[i][j];
	return max;
}

// maximum on the main diagonal of matrix of DOUBLE
double max_diagonal(double array[size][size]) {
	double max = array[0][0];
	for (int i = 1; i < size; i++)
		for (int j = 1; j < size; j++)
			if (i == j && max < array[i][j])
				max = array[i][j];
	return max;
}

// sort the elements of each row of matrix of INT
void sort_asc(int array[size][size]) {
	// loop each row of array
	for (int i = 0; i < size; i++) {
		// sort element of each row, using bubble sort
		for (int j = size-1; j > 0; j--) {
			bool done = true;
			for (int k = 0; k < j; k++) {
				if (array[i][k] > array[i][k+1]) {
					swap(array[i][k], array[i][k+1]);
					done = false;
				}
			}
			if (done) break;
		}
	}
}

// sort the elements of each row of matrix of CHAR
void sort_asc(char array[size][size]) {
	// loop each row of array
	for (int i = 0; i < size; i++) {
		// sort element of each row, using bubble sort
		for (int j = size-1; j > 0; j--) {
			bool done = true;
			for (int k = 0; k < j; k++) {
				if (array[i][k] > array[i][k+1]) {
					swap(array[i][k], array[i][k+1]);
					done = false;
				}
			}
			if (done) break;
		}
	}
}

// sort the elements of each row of matrix of CHAR
void sort_asc(double array[size][size]) {
	// loop each row of array
	for (int i = 0; i < size; i++) {
		// sort element of each row, using bubble sort
		for (int j = size-1; j > 0; j--) {
			bool done = true;
			for (int k = 0; k < j; k++) {
				if (array[i][k] > array[i][k+1]) {
					swap(array[i][k], array[i][k+1]);
					done = false;
				}
			}
			if (done) break;
		}
	}
}
main() {
	srand(time(NULL));
	
	// original matrix
	char array[size][size];
	cout << "original matrix :\n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			array[i][j] = rand() % 26 + 65;
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	// min and max on the diagonal
	cout << "Min on the Diagonal : " << min_diagonal(array) << endl;
	cout << "Max on the Diagonal : " << max_diagonal(array) << endl;
	cout << endl;
	
	// sort, cout
	sort_asc(array);
	cout << "after sorted : \n";
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << array[i][j] << " ";
		}
		cout << endl;
	}
}
