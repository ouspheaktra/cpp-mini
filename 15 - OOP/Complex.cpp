#include <iostream>
#include <string.h>
using namespace std;

class Complex {
	int real, imaginary;
public:
	Complex(int real, int imaginary) : real(real),imaginary(imaginary) { }
	Complex(int real) : Complex(real, 0) { }
	Complex() : Complex(0) { }
	
	operator char* () {
		char out[50] = {'\0'};
		char tmp[20] = {'\0'};
		itoa(real, tmp, 10);
		strcat(out, tmp);
		if (imaginary >= 0)
			strcat(out, "+");
		itoa(imaginary, tmp, 10);
		strcat(out, tmp);
		strcat(out, "i");
		
		char *str = new char[strlen(out) + 1];
		strcpy(str, out);
		return str;
	}
	void operator+= (const Complex &c) { *this = *this + c; }
	void operator-= (const Complex &c) { *this = *this - c; }
	void operator*= (const Complex &c) { *this = *this * c; }
	void operator/= (const Complex &c) { *this = *this / c; }
	Complex operator++ () {
		*this += Complex(1);
		return *this;
	}
	Complex operator++ (int post) {
		Complex c = *this;
		*this += Complex(1);
		return c;
	}
	Complex operator-- () {
		*this -= Complex(1);
		return *this;
	}
	Complex operator-- (int post) {
		Complex c = *this;
		*this -= Complex(1);
		return c;
	}
	Complex operator+ () { return *this; }
	Complex operator- () { return *this * -1; }
	Complex operator+ (const Complex &c) {
		return Complex(
			real + c.real,
			imaginary + c.imaginary
		);
	}
	Complex operator- (const Complex &c) {
		return Complex(
			real - c.real,
			imaginary - c.imaginary
		);
	}
	Complex operator* (const Complex &c) {
		return Complex(
			real*c.real - imaginary*c.imaginary,
			real*c.imaginary + c.real*imaginary
		);
	}
	Complex operator/ (const Complex &c) {
		Complex n = *this * Complex(c.real, -c.imaginary);
		int d = c.real*c.real + c.imaginary*c.imaginary;
		return Complex(
			n.real/d,
			n.imaginary/d
		);
	}
};

int main() {
	cout << Complex(12, 5) / Complex(-1,4);
}
