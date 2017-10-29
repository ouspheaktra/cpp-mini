/*
	Calculate
		the sum of negative elements
		the product of elements located between the min and max elements
		the product of even-numbered elements
		the sum of elements located between the first and the last negative elements
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
main() {
	srand(time(NULL));
	
	const int size = 10;
	int arr[size];
	int sum_neg = 0;		// sum of negative
	int min, max, min_id, max_id;	// minimum, maximum
	int product_even = 0;	// product of even element. (not 1, to prevent it from 1 if no even)
	int first_even_bool = 1;	// act as boolean, indicate it's the first even
	int first_neg_bool = 1;	// act as boolean, indicate it's the first negative
	int first_neg_id = -1;	// id of first negative element (-1 indicate no negative)
	int last_neg_id = 0;	// id of last negative
	int sum_between = 0;	// sum between first and last negative
	
	cout << "NUMBER : ";
	for (int i = 0; i < size; i++) {
		
		// random value
		arr[i] = rand()%20 - 10;
		cout << arr[i] << " ";
		
		// if negative
		if (arr[i] < 0) {

			// sum negative
			sum_neg += arr[i];
			
			// last negative id
			last_neg_id = i;
			
			// first negative
			if (first_neg_bool) {
				first_neg_bool = 0;
				first_neg_id = i;
			}
		}
		
		// if even
		if (arr[i] != 0 && arr[i]%2 == 0) {
			
			// if first even
			if (first_even_bool) {
				product_even = 1;
				first_even_bool = 0;
			}
			
			// product even
			product_even *= arr[i];
		}
		
		// if first iteration
		if (i == 0) {
			
			// value min and max
			min = arr[i];
			max = arr[i];
			min_id = i;
			max_id = i;
			
		// if not first iteration
		} else {
			
			// find min
			if (min > arr[i]) {
				min = arr[i];
				min_id = i;
			}
			
			// find max
			if (max < arr[i]) {
				max = arr[i];
				max_id = i;
			}
		}
	}
	
	// product the elements between minimum and maximum
	int product_between = 0;	// (not 1, to prevent it from 1 if no between)
	int from_id, to_id;
	// if id of min < id of max
	if (min_id < max_id) {	
		from_id = min_id+1;
		to_id = max_id;
	// if id of min > id of max
	} else {				
		from_id = max_id+1;
		to_id = min_id;
	}
	// loop to multiply
	for (int i = from_id; i < to_id; i++) {
		if (i == from_id) product_between = 1;	// make it one, so it won't always 0
		product_between *= arr[i];
	}
	
	// sum elements between first to last negative element
	if (first_neg_id >= 0 && first_neg_id != last_neg_id)
		for (int i = last_neg_id-1; i > first_neg_id; i--)
			sum_between += arr[i];
	
	// display the result
	cout << endl;
	cout << "Sum of Negative : " << sum_neg << endl;
	cout << "Minimum : " << min << endl;
	cout << "Maximum : " << max << endl;
	cout << "Product of Elements located ]Min, Maximum[ elements : " << product_between << endl;
	cout << "Product of Even Element : " << product_even << endl;
	if (first_neg_id >= 0 && first_neg_id != last_neg_id)
		cout << "Sum of Elements located ]First, Last[ Negative elements : " << sum_between;
}
