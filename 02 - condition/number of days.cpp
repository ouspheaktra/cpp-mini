/*
    Number of days between 2 dates
    ---
    input 2 dates
    calculate the number of days between those 2 dates
*/
#include <iostream>
using namespace std;
main() {
	int d1, m1, y1, d2, m2, y2;		// d for day, m for month, y for year
	cout << "Dates One : \n";
	cout << "\tDay : "; cin >> d1;
	cout << "\tMonth : "; cin >> m1;
	cout << "\tYear : "; cin >> y1;
	cout << "Dates Two : \n";
	cout << "\tDay : "; cin >> d2;
	cout << "\tMonth : "; cin >> m2;
	cout << "\tYear : "; cin >> y2;
	
	if (m1 <= 0 || m1 > 12 || m2 <= 0 || m2 > 12)	// invalid month
		cout << "Month cannot be smaller than 1 or greater than 12";
	else if (y1 < 0 || y2 < 0)	// invalid year
		cout << "Year cannot be negative";
	else {
		// if date 2 smaller than date 1, swap it
		if ((y1 > y2) ||
			(y1 == y2 && m1 > m2) ||
			(y1 == y2 && m1 == m2 && d1 > d2)
		) {
			int temp_d1 = d1;
			d1 = d2;
			d2 = temp_d1;
			int temp_m1 = m1;
			m1 = m2;
			m2 = temp_m1;
			int temp_y1 = y1;
			y1 = y2;
			y2 = temp_y1;
		}
		
		int days_in_m1;	// number of days in month1
		switch (m1) {
			case 4: case 6: case 9: case 11:
				days_in_m1 = 30; break;
			case 2:
				days_in_m1 = (y1 % 4 == 0) ? 29 : 28; break;
			default:
				days_in_m1 = 31;
		}
		
		int days_in_m2; // number of days in month2
		switch (m2) {
			case 4: case 6: case 9: case 11:
				days_in_m2 = 30; break;
			case 2:
				days_in_m2 = (y2 % 4 == 0) ? 29 : 28; break;
			default:
				days_in_m2 = 31;
		}

		if (d1 > days_in_m1)	// invalid day one
			cout << "Day of Date One cannot be " << d1;
		else if (d2 > days_in_m1)	// invalid day two
			cout << "Day of Date Two cannot be " << d2;
		else {	// if all is fine
			int days_remain_in_m1 = days_in_m1 - d1;	// days remain in month 1
			int days_remain_in_y1 = days_remain_in_m1; // days remain in year 1
			switch (m1 + 1) {
				case 2: days_remain_in_y1 += 28 + (y1 % 4 == 0 ? 1 : 0);
				case 3: days_remain_in_y1 += 31;
				case 4: days_remain_in_y1 += 30;
				case 5: days_remain_in_y1 += 31;
				case 6: days_remain_in_y1 += 30;
				case 7: days_remain_in_y1 += 31;
				case 8: days_remain_in_y1 += 31;
				case 9: days_remain_in_y1 += 30;
				case 10: days_remain_in_y1 += 31;
				case 11: days_remain_in_y1 += 30;
				case 12: days_remain_in_y1 += 31;
				case 13: days_remain_in_y1 += 0;
			}
			
			int days_in_y2 = d2; // days in year 2
			switch (m2 - 1) {
				case 11: days_in_y2 += 30;
				case 10: days_in_y2 += 31;
				case 9: days_in_y2 += 30;
				case 8: days_in_y2 += 31;
				case 7: days_in_y2 += 31;
				case 6: days_in_y2 += 30;
				case 5: days_in_y2 += 31;
				case 4: days_in_y2 += 30;
				case 3: days_in_y2 += 31;
				case 2: days_in_y2 += 28 + (y2 % 4 == 0 ? 1 : 0);
				case 1: days_in_y2 += 31;
				case 0: days_in_y2 += 0;
			}
			
			// calculate DAYS, the result
			int years_between = y2 - y1 - 1;	// years in between
			int leap_years_in_between = (y2 - 1)/4 - (y1 + 1)/4;
			if (y1 == y2 && y1 % 4 != 0)	// if same year and leap year
				leap_years_in_between = 0;
			int days = 365 * years_between + leap_years_in_between + days_remain_in_y1 + days_in_y2;	// days
			
			// display the result
			cout << "The number of Days between 2 dates above : " << days;
		}
	}
}
