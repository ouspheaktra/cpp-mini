#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
bool isPrime(int number) {
	for (int i = 2; i < number; i++)
		if (number%i == 0) return false;
	return true;
}
main() {
	cout << isPrime(541);
}
