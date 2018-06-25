#include <iostream>
#include <string.h>
using namespace std;

class Flat {
	int area;
	float price;
public:
	Flat(): area(0), price(0) { }
	Flat(int area, float price): area(area), price(price) { }
	void Cout() { cout << area << "m2 : " << price << "$" << endl; }
	short operator== (const Flat &f) { return (area < f.price ? -1 : (area > f.area ? 1 : 0)); }
	short operator> (const Flat &f) { return (price < f.price ? -1 : (price > f.price ? 1 : 0)); }
};

int main() {
	Flat f(25, 32.2);
	Flat f2;
	f2 = f;
	f.Cout();
	f2.Cout();
	cout << (f > Flat(12, 32)) << endl;
	cout << (f == Flat(12, 32));
}
