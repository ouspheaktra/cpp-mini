#include <iostream>
#include <stdlib.h>
using namespace std;

class Binary {
	int decimal;
public:
	Binary():decimal(0) {}
	Binary(int decimal) {
		this->decimal = decimal;
	}
	char * String() {
		char *out = new char[100];
		itoa(decimal, out, 2);
		return out;
	}
	Binary operator+ (const Binary &b) {
		return Binary(decimal + b.decimal);
	}
	Binary operator- (const Binary &b) {
		return Binary(decimal - b.decimal);
	}
	Binary operator* (const Binary &b) {
		return Binary(decimal * b.decimal);
	}
	Binary operator/ (const Binary &b) {
		return Binary(decimal / b.decimal);
	}
};

int main() {
	Binary out = Binary(20) + Binary(40);
	cout << out.String();
}
