#include <iostream>
#include <string>
using namespace std;
string decimalConverter(int number, int base);
main() {
	cout << decimalConverter(2000, 16);
}
string decimalConverter(int number, int base) {
	string result = "";
	for (; number != 0; number /= base) {
		int remainder = number % base;
		if (remainder <= 9)	result = (char)(remainder + '0') + result;
		else				result = (char)(remainder - 10 + 'a') + result;
	}
	return result;
}
