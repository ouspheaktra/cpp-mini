#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
int *allocate_memory(int size) {
	return new int[size];
}
void initialize(int *array, int size) {
	for (int i = 0; i < size; i++)
		array[i] = rand()%10;
}
void print(int *array, int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}
void remove(int **array) {
	delete []*array;
	*array = NULL;
}
void addLast(int **array, int &size, int number) {
	int *temp = allocate_memory(size+1);
	// copy original array to temp
	for (int i = 0; i < size; i++)
		temp[i] = (*array)[i];
	// set last element to a provided number
	temp[size] = number;
	remove(array);
	*array = temp;
	size++;
}
void insertAt(int **array, int &size, int index, int number) {
	int *temp = allocate_memory(++size);
	// copy first part of original array to temp
	for (int i = 0; i < index; i++)
		temp[i] = (*array)[i];
	// set a number at specific index
	temp[index] = number;
	// copy last part of original array to temp
	for (int i = index+1; i < size; i++)
		temp[i] = (*array)[i-1];
	// remove original array
	remove(array);
	*array = temp;
}
void removeAt(int **array, int &size, int index) {
	int *temp = allocate_memory(--size);
	// copy first part
	for (int i = 0; i < index; i++)
		temp[i] = (*array)[i];
	// copy last part
	for (int i = index; i < size; i++)
		temp[i] = (*array)[i+1];
	remove(array);
	*array = temp;
}
main() {
	srand(time(NULL));
	int s = 10;
	int *arr = allocate_memory(s);	// allocate memory
	initialize(arr, s);				// initial value
	print(arr, s);
	addLast(&arr, s, 10);			// add 10 to last
	print(arr, s);
	insertAt(&arr, s, 8, 111);		// insert 111 to index 8		
	print(arr, s);
	removeAt(&arr, s, 8);			// remove from index 8
	print(arr, s);
}
