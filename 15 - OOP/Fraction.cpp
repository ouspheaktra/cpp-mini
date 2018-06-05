#include <iostream>
#include <string.h>
using namespace std;

class Fraction {
	int numerator, denominator;
	
public:
	Fraction(int numerator, int denominator) : numerator(numerator),denominator(denominator) { }
	Fraction(int numerator) : Fraction(numerator, 1) { }
	Fraction() : Fraction(1) { }
	
	operator char* () {
		char out[100] = {'\0'};
		char tmp[20] = {'\0'};
		itoa(numerator, tmp, 10);
		strcat(out, tmp);
		strcat(out, "/");
		itoa(denominator, tmp, 10);
		strcat(out, tmp);
		
		char *str = new char[strlen(out) + 1];
		strcpy(str, out);
		return str;
	}
	void operator+= (Fraction f) {
		*this = *this + f;
	}
	void operator-= (Fraction f) {
		*this = *this - f;
	}
	void operator*= (Fraction f) {
		*this = *this * f;
	}
	void operator/= (Fraction f) {
		*this = *this / f;
	}
	Fraction operator++ () {
		*this += Fraction(1);
		return *this;
	}
	Fraction operator++ (int post) {
		Fraction f = *this;
		*this += Fraction(1);
		return f;
	}
	Fraction operator-- () {
		*this -= Fraction(1);
		return *this;
	}
	Fraction operator-- (int post) {
		Fraction f = *this;
		*this -= Fraction(1);
		return f;
	}
	Fraction operator+ (Fraction f) {
		return Fraction(
			numerator*f.denominator + denominator*f.numerator,
			denominator*f.denominator
		);
	}
	Fraction operator- (Fraction f) {
		return Fraction(
			numerator*f.denominator - denominator*f.numerator,
			denominator*f.denominator
		);
	}
	Fraction operator* (Fraction f) {
		return Fraction(
			numerator*f.numerator,
			denominator*f.denominator
		);
	}
	Fraction operator/ (Fraction f) {
		return Fraction(
			numerator*f.denominator,
			denominator*f.numerator
		);
	}
};

int main() {
	Fraction f(2, 5);
}
