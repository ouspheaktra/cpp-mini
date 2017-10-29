/***
	Calculate the Travel Distance
	using a formula distance = speed * time + (acceleration * time * time) / 2
	by Ouspheaktra Phal
***/

#include <iostream>
using namespace std;
main() {
	
	// intro
	cout << "Calculate the Travel Distance\n";
	cout << "(require speed, time, acceleration)\n";
	cout << "---------------\n";
	
	// declare speed, time, acceleration and ask for value
	float speed, time, acceleration;
	cout << "Input Speed : ";
	cin >> speed;
	cout << "Input Time : ";
	cin >> time;
	cout << "Input acceleration : ";
	cin >> acceleration;
	
	// calculate the distance
	float distance = speed * time + (acceleration * time * time) / 2;
	
	// show the result
	cout << "---------------\n";
	cout << "The Travel Distance is " << distance;
	
}
