#ifndef TIME_H
#define TIME_H

#include "string.h"

class Time {
	int hour, minute, second;
public:
	Time();
	Time(int hour, int minute, int second);
	
	void SetNow();
	void SetAllMinutes(int minute);
	void SetTime(int hour, int minute, int second);
	void SetAmericanTime(int hour, int minute, int second, bool am);
	
	int GetHour();
	int GetMinute();
	int GetSecond();
	
	int GetAllMinutes() const;
	short Compare(const Time &t);
	String ToString ();
	Time operator+ (const Time &t);
	Time operator- (const Time &t);
	bool operator> (const Time &t);
};
#endif
