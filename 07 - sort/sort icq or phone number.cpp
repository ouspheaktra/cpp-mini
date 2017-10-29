/*
	Input ICQ and Phone number
	Sort by ICQ or Phone number
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;
int main() {
	const int size = 5;
	int icq[size];
	int num[size];
	//srand(time(NULL));	/* TESTING ONLY */
	
	// ask to input ICQ and Phone Number
	for (int i = 0; i < size; i++) {
		/*	TESTING ONLY
		icq[i] = rand()%9000 + 1000;
		num[i] = (rand()%9000 + 1000)*10000 + (rand()%9000 + 1000);
		cout << "ICQ : " << icq[i] << "\t Phone : 0" << num[i] << endl;*/
		cout << "ICQ : "; cin >> icq[i];
		cout << "Phone Number : "; cin >> num[i];
		cout << endl;
	}
	
	// ask to sort by ICQ or Phone Number
	int option;
	cout << "1 : Sort by ICQ" << endl;
	cout << "2 : Sort by Phone Number" << endl;
	while (1) {
		cout << "Choose "; cin >> option;
		if (option == 1 || option == 2)	break;
		else							cout << "1 or 2, not " << option << endl;
	}
	
	// sort using bubble algorithm
	int done, i, j, compare;
	for (i = size-1; i > 0; i--) {
		done = true;	// presume there is nothing to swap
		for (j = 0; j < i; j++) {
			
			// different comparison according to sorting of ICQ or Phone Number
			switch (option) {
				case 1:	compare = icq[j] > icq[j+1]; break;
				case 2:	compare = num[j] > num[j+1];
			}
			
			// compare to bubble (swap)
			if (compare) {
				swap(num[j], num[j+1]);
				swap(icq[j], icq[j+1]);
				done = false;
			}
		}
		
		// if nothing swapped, break
		if (done) break;
	}
	
	// display the everything after sorted
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << "ICQ : " << icq[i] << "\t Phone Number : 0" << num[i] << endl;
	}
}
