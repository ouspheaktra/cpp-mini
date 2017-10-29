/* LUCKY 6-digits NUMBER */
#include <iostream>
using namespace std;

bool isLucky(int number);

main() {
	cout << isLucky(123123);
}

bool isLucky(int number) {
	if (number < 100000 || number > 999999)	return false;
	int n1 = number%10;
	int n2 = number/10%10;
	int n3 = number/100%10;
	int n4 = number/1000%10;
	int n5 = number/10000%10;
	int n6 = number/100000;
	return n1+n2+n3 == n4+n5+n6;
}
