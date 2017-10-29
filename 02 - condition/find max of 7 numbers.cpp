/*
    Find the maximum number of 7 numbers
    ---
    input 7 numbers and find the greatest
*/
#include <iostream>
using namespace std;
main() {
	// ask for 7 numbers
	float n1, n2, n3, n4, n5, n6, n7, max;
	cout << "Please input 7 numbers :\n";
	cin >> n1 >> n2 >> n3 >> n4 >> n5 >> n6 >> n7;
	
	// find the maximum number
	max = (n1 > n2) ? n1 : n2;
	max = (max > n3) ? max : n3;
	max = (max > n4) ? max : n4;
	max = (max > n5) ? max : n5;
	max = (max > n6) ? max : n6;
	max = (max > n7) ? max : n7;
	
	// display the maximum number
	cout << "The maximum number is " << max;
}
