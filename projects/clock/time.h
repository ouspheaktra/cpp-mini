#ifndef TIME_H
#define TIME_H

#include "string.h"
#include <time.h>

class Time {
	int hour, minute, second;
public:
	Time() {
		SetTime(0, 0, 0);
	}
	Time(int hour, int minute, int second) {
		SetTime(hour, minute, second);
	}
	
	void SetNow() {
		time_t rawtime;
		struct tm *timeinfo;
		time( &rawtime );
		timeinfo = localtime( &rawtime );
		this->hour = timeinfo->tm_hour;
		this->minute = timeinfo->tm_min;
		this->second = timeinfo->tm_sec;
	}
	void SetAllMinutes(int minute) {
		this->hour = minute/60;
		this->minute = minute%60;
		this->second = 0;
	}
	void SetTime(int hour, int minute, int second) {
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}
	void SetAmericanTime(int hour, int minute, int second, bool am) {
		if (am && hour == 12)	hour = 0;
		else
		if (!am && hour != 12)	hour += 12;
		this->hour = hour;
		this->minute = minute;
		this->second = second;
	}
	
	int GetHour() { return hour; }
	int GetMinute() { return minute; }
	int GetSecond() { return second; }
	
	int GetAllMinutes() const {
		return hour*60 + minute;
	}
	short Compare(const Time &t) {
		if (this->GetAllMinutes() > t.GetAllMinutes())
			return 1;
		else if (this->GetAllMinutes() < t.GetAllMinutes())
			return -1;
		else
			return 0;
	}
	String ToString () {
		return String(hour) + String(":") + String(minute);
	}
	Time operator+ (const Time &t) {
		Time out;
		out.SetAllMinutes(this->GetAllMinutes() + t.GetAllMinutes());
		return out;
	}
	Time operator- (const Time &t) {
		Time out;
		out.SetAllMinutes(this->GetAllMinutes() - t.GetAllMinutes());
		return out;
	}
	bool operator> (const Time &t) {
		return (this->Compare(t) == 1);
	}
};


/*
#include <iostream>
int main() {
	Time t;
	t.SetNow();
	std::cout << t.ToString();
}
*/
#endif
