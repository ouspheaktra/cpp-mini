/* BULLS N COWS */

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
void splitNumber(int number, int array[], int size) {
	for (; number != 0; number /= 10)
		array[--size] = number%10;
}
main() {
	srand(time(NULL));
	
	// prepare the game
	cout << "--- welcome to BULLS & COWS game ---\n\n";
	int number[100] = {0};
	int size = 0;	// number of number that the user have guessed
	// random the result
	const short digit = 4;
	int result = rand()%9000 + 1000;
	// cout << result << endl;	// uncomment to TEST THE RESULT
	int resultArr[digit];
	splitNumber(result, resultArr, digit);	// split result to result in array

	// loop until the user guesses right
	while(1) {
		// input a number to guess
		cout << "input a " << digit << "-digits number : ";
		cin >> number[size];
		if (number[size] < 1000 || number[size] > 9999) {
			cout << "!!! " << digit << "-DIGITS NUMBER PLEASE !!!\n";
			continue;
		} else {
		
		// bulls and cows
		int bulls = 0;
		int cows = 0;
		// inputted number as array
		int numberArr[digit];
		splitNumber(number[size], numberArr, digit);
		// loop to find bulls and cows
		for (int i = 0; i < digit; i++) {	// loop each digit of guessed number
			int isBull = false;
			int isCow = false;
			for (int j = 0; j < digit; j++) {	// loop each digit of result
				if (resultArr[j] == numberArr[i]) {	// if the same
					if (i == j) {	// if it's the same place. it's cow
						isCow = true;
						break;
					} else {		// if not the same place. it's bull
						isBull = true;
					}
				}
			}
			// increse number of bulls or cows
			if (isCow)			cows++;
			else if (isBull)	bulls++;
		}
		// if 4 cows, RIGHT
		if (cows == 4) {
			size++;
			break;
		}
		// output bulls and cows
		cout << bulls << " bulls\n";
		cout << cows << " cows\n";
		size++;
		}
	}
	
	// output the winning message
	cout << "---\n";
	cout << "You guess it right\n";
	cout << "The correct number is " << result << endl;;
	cout << "These all the numbers you'd guessed.\n";
	for (int i = 0; i < size; i++)
		cout << number[i] << endl;
}
