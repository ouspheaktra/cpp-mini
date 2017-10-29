/* SUM NUMBER IN RANGE */
#include <iostream>
using namespace std;

long sumBetween(int start, int end);	// sum the number from start to end

main() {
	cout << sumBetween(1, 5);
}

long sumBetween(int start, int end) {
	if (start > end) {
		int temp = end;
		end = start;
		start = temp;
	}
	long result = 0;
	for (int i = start; i <= end; i++)	result += i;
	return result;
}
