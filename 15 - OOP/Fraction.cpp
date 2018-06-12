#include <iostream>
#include <string.h>
using namespace std;

class Fraction {
	int numerator, denominator;
	short Compare(const Fraction &f) {
		float	one = (float)numerator/denominator,
				two = (float)f.numerator/f.denominator;
		if (one > two)
			return 1;
		else if (one < two)
			return -1;
		return 0;
	}
public:
	Fraction(int numerator, int denominator) : numerator(numerator),denominator(denominator) {
		if (numerator < 0 && denominator < 0) {
			this->numerator = -numerator;
			this->denominator = -denominator;
		}
	}
	Fraction(int numerator) : Fraction(numerator, 1) { }
	Fraction() : Fraction(1) { }
	
	operator char* () {
		char out[50] = {'\0'};
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
	void operator+= (const Fraction &f) { *this = *this + f; }
	void operator-= (const Fraction &f) { *this = *this - f; }
	void operator*= (const Fraction &f) { *this = *this * f; }
	void operator/= (const Fraction &f) { *this = *this / f; }
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
	Fraction operator+ () { return *this; }
	Fraction operator- () { return *this * -1; }
	Fraction operator+ (const Fraction &f) {
		return Fraction(
			numerator*f.denominator + denominator*f.numerator,
			denominator*f.denominator
		);
	}
	Fraction operator- (const Fraction &f) {
		return Fraction(
			numerator*f.denominator - denominator*f.numerator,
			denominator*f.denominator
		);
	}
	Fraction operator* (const Fraction &f) {
		return Fraction(
			numerator*f.numerator,
			denominator*f.denominator
		);
	}
	Fraction operator/ (const Fraction &f) {
		return Fraction(
			numerator*f.denominator,
			denominator*f.numerator
		);
	}
	bool operator> (const Fraction &f) { return (Compare(f) == 1); }
	bool operator< (const Fraction &f) { return (Compare(f) == -1); }
	bool operator== (const Fraction &f) { return (Compare(f) == 0); }
	bool operator>= (const Fraction &f) { return (Compare(f) >= 0); }
	bool operator<= (const Fraction &f) { return (Compare(f) <= 0); }
};

int main() {
	cout << -Fraction(-2, -5) << endl;
	cout << (Fraction(1/3) >= Fraction(1/3));
}
