/* GREATEST COMMON DIVISORS */

#include <iostream>
using namespace std;
int gcd(int number1, int number2) {
	
	// find all divisors of number1
	int divisor1[100] = {0};
	int size1 = 0;
	for (int i = 1; i < number1; i++)
		if (number1 % i == 0)
			divisor1[size1++] = i;
	
	// find all divisors of number2
	int divisor2[100] = {0};
	int size2 = 0;
	for (int i = 1; i < number2; i++)
		if (number2 % i == 0)
			divisor2[size2++] = i;
	
	// look for the same and the greatest
	for (int i = size1-1; i >= 0; i--)
		for (int j = size2-1; j >= 0; j--)
			if (divisor1[i] == divisor2[j])
				return divisor1[i];
}
main() {
	cout << gcd(48, 180);
}
