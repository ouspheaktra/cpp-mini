#include <iostream>
#include <string.h>
using namespace std;

class Coat {
	char * type;
	float price;
public:
	Coat(): type(NULL), price(0) { }
	Coat(const char * type, float price) {
		this->type = new char[strlen(type) + 1];
		strcpy(this->type, type);
		this->price = price;
	}
	void Cout() {
		cout << type << " " << price << "$" << endl;
	}
	short operator== (const Coat &c) { return strcmp(type, c.type); }
	short operator> (const Coat &c) { return (price < c.price ? -1 : (price > c.price ? 1 : 0)); }
	void operator= (const Coat &c) {
		if (type)
			delete [] type;
		type = new char[strlen(c.type) + 1];
		strcpy(type, c.type);
		price = c.price;
	}
};

int main() {
	cout << (Coat("lala", 12.5) == Coat("no", 68)) << endl;
	cout << (Coat("yew", 54) > Coat("ewr", 15));
}
