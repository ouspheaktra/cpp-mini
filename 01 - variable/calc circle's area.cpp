/***
	Calculate the Area of a Circle
	require the length of a circle
	by Ouspheaktra Phal
***/

#include <iostream>
using namespace std;
main() {
	
	// intro
	cout << "Calculate the Area of a Circle\n";
	cout << "(require the length of a circle)\n";
	cout << "---------------\n";
	
	// declare length of circle and ask for value
	float length;
	cout << "Please input the Length of a Circle : ";
	cin >> length;
	
	// calculate the radius
	const float pi = 3.14;	// declare PI
	float radius = length / (2 * pi);
	
	// calculate the area
	float area = pi * radius * radius;
	
	// show the result
	cout << "---------------\n";
	cout << "The Area of the Circle above is " << area;
	
}
