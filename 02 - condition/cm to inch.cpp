/* 
	Centimeter and Inch converter 
*/

#include <iostream>
using namespace std;
main() {
	float num;
	float cm_per_inch = 2.54;
	int type;

	// ask for converter
	cout << "Please input\n";
	cout << "\t0 for Inch to Centimeter\n";
	cout << "\t1 for Centimeter to Inch\n";
	cin >> type;

	cout << "---\n";
	
	// if the input is not valid
	if (type != 1 && type != 0) {
		cout << "1 or 0, not " << type;
		
	// if it's a INCH to CM converter
	} else if (type == 0) {
		cout << "Please input a number (in inch) : "; cin >> num;	// ask for inch
		cout << num << " inch = " << num * cm_per_inch << " cm";	// display in inch
	
	// if it's a CM to INCH converter
	} else {
		cout << "Please input a number (in cm) : "; cin >> num;		// ask for cm
		cout << num << " cm = " << num / cm_per_inch << " inch\n";	// display in inch
	}
}
