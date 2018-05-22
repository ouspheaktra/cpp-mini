#include <iostream>
using namespace std;

class Fraction {
	int numerator, denominator;
	
	public:
	Fraction(int n, int d) {
		numerator = n;
		denominator = d;
	}
	int GetNumerator() {
		return numerator;
	}
	int GetDenominator() {
		return denominator;
	}
	void Add(Fraction other) {
		numerator = numerator*other.GetDenominator() + denominator*other.GetNumerator();
		denominator *= other.GetDenominator();
	}
	void Subtract(Fraction other) {
		numerator = numerator*other.GetDenominator() - denominator*other.GetNumerator();
		denominator *= other.GetDenominator();
	}
	void Multiply(Fraction other) {
		numerator *= other.GetNumerator();
		denominator *= other.GetDenominator();
	}
	void Divide(Fraction other) {
		numerator *= other.GetDenominator();
		denominator *= other.GetNumerator();
	}
};

int main() {
	Fraction	one(2, 3),
				two(3, 4);
	one.Add(two);
	cout << one.GetNumerator() << "\n---\n" << one.GetDenominator();
}
