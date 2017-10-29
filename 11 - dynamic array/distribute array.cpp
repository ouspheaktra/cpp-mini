#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void print(int *array, int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << " ";
	cout << endl;
}
int countPositive(int *array, int size) {
	int count = 0;
	for (int i = 0; i < size; i++)
		count += array[i] > 0;
	return count;
}
int countNegative(int *array, int size) {
	int count = 0;
	for (int i = 0; i < size; i++)
		count += array[i] < 0;
	return count;
}
int countZero(int *array, int size) {
	int count = 0;
	for (int i = 0; i < size; i++)
		count += (array[i] == 0);
	return count;
}
void distribute(int *array, int size, int **positive, int &positiveSize, int **negative, int &negativeSize, int **zero, int &zeroSize) {
	positiveSize = countPositive(array, size);
	negativeSize = countNegative(array, size);
	zeroSize = countZero(array, size);
	*positive = new int[positiveSize];
	*negative = new int[negativeSize];
	*zero = new int [negativeSize];
	for (int i = 0, p = 0, n = 0, z = 0; i < size; i++) {
		if (array[i] > 0)
			(*positive)[p++] = array[i];
		else if (array[i] < 0)
			(*negative)[n++] = array[i];
		else
			(*zero)[z++] = array[i];
	}
}
main() {
	srand(time(NULL));
	const int s = 10;
	int arr[s];
	for (int i = 0; i < s; i++)
		arr[i] = rand()%200 - 100;
	print(arr, s);
	int *pos;
	int posSize;
	int *neg;
	int negSize;
	int *zer;
	int zerSize;
	distribute(arr, s, &pos, posSize, &neg, negSize, &zer, zerSize);
	cout << posSize << " positive : ";
	print(pos, posSize);
	cout << negSize << " negative : ";
	print(neg, negSize);
	cout << zerSize << " zero     : ";
	print(zer, zerSize);
}
