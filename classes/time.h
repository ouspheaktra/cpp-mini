#ifndef TIME_H
#define TIME_H

#include "string.h"
#include <time.h>

class Date {
	int day, date, month, year;
public:
	Date();
	Date(int date, int month, int year);

	void SetNow();
	void SetDate(int date, int month, int year);

	int GetDay();
	int GetDate();
	int GetMonth();
	int GetYear();

	String ToString();
	static const String Day[];
};

class Time {
	int hour, minute, second;
public:
	Time();
	Time(int hour, int minute, int second);
	
	void SetNow();
	void SetAllMinutes(int minute);
	void SetAllSeconds(int second);
	void SetTime(int hour, int minute, int second);
	void SetAmericanTime(int hour, int minute, int second, bool am);
	
	int GetHour();
	int GetMinute();
	int GetSecond();
	
	int GetAllMinutes() const;
	short Compare(const Time &t);
	String ToString();
	Time operator+ (const Time &t);
	Time operator- (const Time &t);
	bool operator> (const Time &t);
};
#endif
