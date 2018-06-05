#include <iostream>
#include <stdlib.h>
#include <string.h>
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
	operator char* () {
		return String();
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
	Binary &operator++() {			// pre
		decimal++;
		return *this;
	}
	Binary operator++(int post) {	// post
		decimal++;
		return Binary(decimal - 1);
	}
	Binary &operator--() {			// pre
		decimal--;
		return *this;
	}
	Binary operator--(int post) {	// post
		decimal--;
		return Binary(decimal + 1);
	}
	char * operator[] (const char * s) {
		char * d = new char[strlen(s) + 1];
		strcpy(d, s);
		return d;
	}
};

int main() {
	Binary b(13);
	cout << b["hello world"];
}
