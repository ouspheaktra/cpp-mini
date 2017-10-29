/* POWER FUNC */
#include <iostream>
using namespace std;

double power(int base, int exponent);

main() {
	cout << power(7, 8);
}

double power(int base, int exponent) {
	double result = 1;
	int isNegative = exponent < 0;
	if (isNegative)	exponent = -exponent;
	for (int i = 0; i < exponent; i++)	result *= base;
	if (isNegative)	return 1/result;
	return result;	
}
