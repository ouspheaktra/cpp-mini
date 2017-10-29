/*
	The user enters a company's profit for the year (12 months).
	The user then enters a range (for example, 3 and 6 - a search between the 3rd and 6th months).
	It is necessary to determine a month in which the profit was maximal, and a month in which the profit was minimal in view of the selected range.
*/
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
using namespace std;
main() {
	srand(time(NULL));
	
	const int size = 12;
	int profit[size];
	
	while (1) {
		
		// input profits
		cout << "Input the profit for 12 months" << endl;
		for (int i = 0; i < size; i++) {
			cout << "\tMonth " << i+1 << " : ";
			cin >> profit[i];
		}
		
		int from, to;
		cout << "Find the minimal and maximal" << endl;
		
		// from month
		while (1) {
			cout << "\tFrom month "; cin >> from;
			if (from <= 0 || from > size) cout << "\tCannot be " << from << endl;
			else break;
		}
		
		// to month
		while (1) {
			cout << "\tTo month "; cin >> to;
			if (to < from || to > size) cout << "\tCannot be " << to << endl;
			else break;
		}
		
		// find minimal and maximal
		int min = profit[from-1], max = profit[from-1];
		for (int i = from; i < to; i++) {
			if (min > profit[i]) min = profit[i];
			if (max < profit[i]) max = profit[i];
		}
		
		// display result
		cout << "the MINIMAL PROFIT from month " << from << " to month " << to << " is " << min << endl;
		cout << "the MAXIMAL PROFIT from month " << from << " to month " << to << " is " << max << endl;		
		cout << " --- " << endl;
		
		// ask for continue or not
		char answer;
		int yes = 0;
		while (1) {
			cout << "Continue using this tool ? Y/N "; cin >> answer;
			
			// if Y
			if (answer == 'Y' || answer == 'y') {
				yes = 1;
				break;
				
			// if N
			} else if (answer == 'N' || answer == 'n') break;
			
			// if invalid answer
			else cout << "Y or N, not " << answer;
		}
		
		// if continue or not
		if (yes == 0) break;
		else system("cls");
	}
	
	cout << "Bye";
}
