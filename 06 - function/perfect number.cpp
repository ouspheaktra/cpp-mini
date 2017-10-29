/* PERFECT NUMBER */
#include <iostream>
using namespace std;

bool isPerfect(int number);
int countPerfectBetween(int start, int end);	// how many perfect number is there from start to end?

main() {
	cout << "There are " << countPerfectBetween(0, 30) << " perfect numbers from 0 to 30." << endl << endl;
	for (int i = 0; i <= 30; i++) 
		cout << i << " : " << isPerfect(i) << endl;
}

bool isPerfect(int number) {
	if (number < 2) return false;
	int sumDivisor = 1;
	for (int i = 2; i < number; i++) {
		if (number%i == 0)
			sumDivisor += i;
	}
	return sumDivisor == number;
}

int countPerfectBetween(int start, int end) {
	int result = 0;
	if (start > end) {
		int temp = end;
		end = start;
		start = temp;
	}
	for (int i = start; i <= end; i++) result += isPerfect(i);
	return result;
}
