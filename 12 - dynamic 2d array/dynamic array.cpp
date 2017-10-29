#include <iostream>
using namespace std;

/* allocate memroy for 2D array */
int **allocate_memory(int row, int col) {
	int **arr = new int*[row];
	for (int i = 0; i < row; i++)
		arr[i] = new int[col];
	return arr;
}
/* initialize value for 2D array */
void initialize(int **array, int row, int col) {
	int num = 10;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			array[i][j] = num++;
}
/* print 2D array */
void print(int **array, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}
/* remove 2d array */
void remove(int ***array, int row) {
	for (int i = 0; i < row; i++)
		delete[](*array)[i];
	delete[]*array;
	*array = NULL;
}
/* insert a number into 2D array at specific column of all rows */
void insert_col(int ***array, int row, int &col, int index, int number) {
	int **temp = allocate_memory(row, col+1);
	// prepare value for temp
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col+1; j++)
			// copy first part of original array to temp
			if (j < index)
				temp[i][j] = (*array)[i][j];
			// set a number at specific index
			else if (j == index)
				temp[i][j] = number;
			// copy last part of original array to temp
			else
				temp[i][j] = (*array)[i][j-1];
	// remove original array
	remove(array, row);
	*array = temp;
	col++;
}
/* insert a number into 2D array at all columns of specific row */
void insert_row(int ***array, int &row, int col, int index, int number) {
	int **temp = allocate_memory(row+1, col);
	// prepare value for temp
	for (int i = 0; i < row+1; i++)
		for (int j = 0; j < col; j++)
			// copy first part of original array to temp
			if (i < index)
				temp[i][j] = (*array)[i][j];
			// set a number at specific index
			else if (i == index)
				temp[i][j] = number;
			// copy last part of original array to temp
			else
				temp[i][j] = (*array)[i-1][j];
	// remove original array
	remove(array, row);
	*array = temp;
	row++;
}
void remove_col(int ***array, int row, int &col, int index) {
	int **temp = allocate_memory(row, col-1);
	// prepare value for temp
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col-1; j++)
			// copy first part
			if (j < index)
				temp[i][j] = (*array)[i][j];
			// copy last part
			else
				temp[i][j] = (*array)[i][j+1];
	remove(array, row);
	*array = temp;
	col--;
}
void remove_row(int ***array, int &row, int col, int index) {
	int **temp = allocate_memory(row-1, col);
	// prepare value for temp
	for (int i = 0; i < row-1; i++)
		for (int j = 0; j < col; j++)
			// copy first part
			if (i < index)
				temp[i][j] = (*array)[i][j];
			// copy last part
			else
				temp[i][j] = (*array)[i+1][j];
	remove(array, row);
	*array = temp;
	row--;
}

/* shifting dynamic 2d array */
void shift_right(int **array, int row, int col, int step) {
	if (step != 1)
		shift_right(array, row, col, step-1);
	for (int r = 0; r < row; r++)
		for (int c = col-1; c > 0; c--)
			swap(array[r][c], array[r][c-1]);
}
void shift_left(int **array, int row, int col, int step) {
	if (step != 1)
		shift_left(array, row, col, step-1);
	for (int r = 0; r < row; r++)
		for (int c = 0; c < col-1; c++)
			swap(array[r][c], array[r][c+1]);
}
void shift_up(int **array, int row, int col, int step) {
	if (step != 1)
		shift_up(array, row, col, step-1);
	for (int c = 0; c < col; c++)
		for (int r = 0; r < row-1; r++)
			swap(array[r][c], array[r+1][c]);
}
void shift_down(int **array, int row, int col, int step) {
	if (step != 1)
		shift_down(array, row, col, step-1);
	for (int c = 0; c < col; c++)
		for (int r = row-1; r > 0; r--)
			swap(array[r][c], array[r-1][c]);
}

/* transpose matrix (2d array) */
void transpose(int ***array, int &row, int &col) {
	swap(row, col);
	int **temp = allocate_memory(row, col);
	// prepare value for temp
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			temp[i][j] = (*array)[j][i];
	// remove original array
	remove(array, col);
	*array = temp;
}

int main() {
	int row = 5;
	int col = 8;
	int **arr = allocate_memory(row, col);
	initialize(arr, row, col);
	
	cout << "original\n";
	print(arr, row, col);
	
	cout << "insert 11 to col 2\n";
	insert_col(&arr, row, col, 2, 11);
	print(arr, row, col);
	
	cout << "insert 22 to row 3\n";
	insert_row(&arr, row, col, 3, 22);
	print(arr, row, col);
	
	cout << "remove col 2\n";
	remove_col(&arr, row, col, 2);
	print(arr, row, col);
	
	cout << "remove row 3 (back to original)\n";
	remove_row(&arr, row, col, 3);
	print(arr, row, col);
	
	cout << "shift right 3\n";
	shift_right(arr, row, col, 3);
	print(arr, row, col);
	
	cout << "shift left 3 (back to original)\n";
	shift_left(arr, row, col, 3);
	print(arr, row, col);
	
	cout << "shift up 3\n";
	shift_up(arr, row, col, 3);
	print(arr, row, col);
	
	cout << "shift down 3 (back to original)\n";
	shift_down(arr, row, col, 3);
	print(arr, row, col);
	
	cout << "transposed\n";
	transpose(&arr, row, col);
	print(arr, row, col);
	
	cout << "transposed one more time (back to original)\n";
	transpose(&arr, row, col);
	print(arr, row, col);
}
