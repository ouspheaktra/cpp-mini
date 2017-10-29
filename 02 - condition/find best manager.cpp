/*
    BEST MANAGER
    ---
    Manager's salary is $ 200 + a percentage of sales
	the selling 
		up to $ 500 - 3 %,
		from 500 to 1000 - 5 %
		over 1000 - 8 %.
	The user enters from the keyboard a level of sales for three managers.
	Determine their salaries, determine who is the best manager,
	overcharging him a bonus of $ 200 output the results to the screen.
*/
#include <iostream>
using namespace std;
main() {
	// ask for 7 numbers
	float m1, m2, m3;	// m for manager
	cout << "Input the SALES of 1st manager : "; cin >> m1;
	cout << "Input the SALES of 2nd manager : "; cin >> m2;
	cout << "Input the SALES of 3rd manager : "; cin >> m3;
	
	if (m1 < 0 || m2 < 0 || m3 < 0)
		cout << "SALES cannot be Negative";
	else {
		int salary = 200;
		
		// calculate percentage
		float p1, p2, p3;	// p for percentage that each manager gets more
		p1 = m1 < 500 ? 0.03 : (m1 <= 1000 ? 0.05 : 0.08);
		p2 = m2 < 500 ? 0.03 : (m2 <= 1000 ? 0.05 : 0.08);
		p3 = m3 < 500 ? 0.03 : (m3 <= 1000 ? 0.05 : 0.08);
		
		// salary for each manager
		float s1 = salary + m1 * p1;
		float s2 = salary + m2 * p2;
		float s3 = salary + m3 * p3;
		
		// display salary
		cout << "1st manager get " << s1 << endl;
		cout << "2nd manager get " << s2 << endl;
		cout << "3rd manager get " << s3 << endl;
		
		// give bonus
		if (m1 > m2 && m1 > m3)
			cout << "1st manager is the best manager. He gets bonus 200$. So all, he gets " << 200 + s1 << "$.";
		else if (m2 > m1 && m2 > m3)
			cout << "2nd manager is the best manager. He gets bonus 200$. So all, he gets " << 200 + s2 << "$.";
		else if (m3 > m2 && m3 > m1)
			cout << "3rd manager is the best manager. He gets bonus 200$. So all, he gets " << 200 + s3 << "$.";
	}
}
