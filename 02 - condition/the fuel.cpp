/*
    THE FUEL
    ---
    The cargo aircraft should fly with a cargo from point A to point C through point B.
	The fuel tank capacity of the cargo aircraft is 300 liters.
	The fuel consumption per 1 km, depending on the weight of cargo of the aircraft, is following:
		up to 500 kg: 1 liter / km;
		up to 1000 kg: 4 liters / km;
		up to 1500 kg: 7 liters / km;
		up to 2000 kg: 9 liters / km;
		more than 2,000 kg - the plane does not lift.
	The user inputs a distance between points A and B, B and C, and the weight of cargo.
	The program must calculate what minimum amount of fuel is necessary for refueling the aircraft in point B, in order to fly from point A to point C.
	If you can’t overcome any of given distances
	The program should display a message about the impossibility to fly according to the entered route.
*/
#include <iostream>
using namespace std;
main() {
	
	// ask for A to B, B to C and Weight of Cargo
	float AB, BC, weight;
	cout << "Input the distance from A to B (km) : "; cin >> AB;
	cout << "Input the distance from B to C (km) : "; cin >> BC;
	cout << "Input the weight of cargo (kg) : "; cin >> weight;
	
	// if negative
	if (weight < 0 || AB < 0 || BC < 0)
		cout << "CANNOT be NEGATIVE";
		
	// if too much weight
	else if (weight > 2000)
		cout << "The plane does NOT LIFT";
	
	// if everything is fine
	else {
		float max_distance, liter_per_km;
		float max_fuel = 300;
		
		// define liter per km
		if (weight <= 500)
			liter_per_km = 1;
		else if (weight <= 1000)
			liter_per_km = 4;
		else if (weight <= 1500)
			liter_per_km = 7;
		else if (weight <= 2000)
			liter_per_km = 9;
		
		// maximum distance
		max_distance = max_fuel / liter_per_km;
		
		// if cannot reach B
		if (AB > max_distance)
			cout << "Can NOT reach B";
			
		// if cannot reach C
		else if (BC > max_distance)
			cout << "Can reach B but NOT C";
		
		// if reach C
		else {
			float distance_remain = (AB + BC) - max_distance;		// remaining distance
			float fuel_require = distance_remain * liter_per_km;	// fuel require
			
			// if no need to refuel
			if (fuel_require <= 0)
				cout << "No need to refuel, you can reach C";
			
			// find fuel needed
			else
				cout << "at B, you need to refuel at least " << fuel_require;
		}	
	}
}
