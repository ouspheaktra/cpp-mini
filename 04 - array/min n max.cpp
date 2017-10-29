/* 
	Find Min and Max of the Numbers in a Array
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
main() {
	srand(time(NULL));
	
	const int size = 10;
	int arr[size];
	int min, max;
	
	for (int i = 0; i < size; i++) {
		// random
		arr[i] = rand()%100;
		
		// if first iteration
		if (i == 0) {
			min = arr[i];
			max = arr[i];
			
		//if not first iteration
		} else {
			if (min > arr[i]) min = arr[i];
			if (max < arr[i]) max = arr[i];
		}
		cout << arr[i] << " ";
	}
	
	cout << endl << "MIN : " << min;
	cout << endl <<  "MAX : " << max;
}
