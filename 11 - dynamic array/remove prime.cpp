#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
bool isPrime(int number) {
	for (int i = 2; i < number; i++)
		if (number%i == 0) return false;
	return true;
}
void initialize(int *array, int size) {
	for (int i = 0; i < size; i++)
		array[i] = rand()%100;
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
int countPrime(int *array, int size) {
	int count = 0;
	for (int i = 0; i < size; i++)
		count += isPrime(array[i]);
	return count;
}
void removePrime(int **array, int &size) {
	int newSize = size-countPrime(*array, size);
	int *temp = new int[newSize];
	for (int i = 0, j = 0; i < size; i++)
		if (!isPrime((*array)[i]))
			temp[j++] = (*array)[i];
	remove(array);
	*array = temp;
	size = newSize;
}
main() {
	srand(time(NULL));
	int s = 10;
	int *arr = new int[s];
	initialize(arr, s);
	print(arr, s);
	removePrime(&arr, s);
	print(arr, s);
}
