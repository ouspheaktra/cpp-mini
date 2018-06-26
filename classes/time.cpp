#include "time.h"
#include "string.h"
#include <time.h>

Time::Time() {
	SetTime(0, 0, 0);
}
Time::Time(int hour, int minute, int second) {
	SetTime(hour, minute, second);
}

void Time::SetNow() {
	time_t rawtime;
	struct tm *timeinfo;
	time( &rawtime );
	timeinfo = localtime( &rawtime );
	this->hour = timeinfo->tm_hour;
	this->minute = timeinfo->tm_min;
	this->second = timeinfo->tm_sec;
}
void Time::SetAllMinutes(int minute) {
	this->hour = minute/60;
	this->minute = minute%60;
	this->second = 0;
}
void Time::SetTime(int hour, int minute, int second) {
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}
void Time::SetAmericanTime(int hour, int minute, int second, bool am) {
	if (am && hour == 12)	hour = 0;
	else
	if (!am && hour != 12)	hour += 12;
	this->hour = hour;
	this->minute = minute;
	this->second = second;
}

int Time::GetHour() { return hour; }
int Time::GetMinute() { return minute; }
int Time::GetSecond() { return second; }

int Time::GetAllMinutes() const {
	return hour*60 + minute;
}
short Time::Compare(const Time &t) {
	if (this->GetAllMinutes() > t.GetAllMinutes())
		return 1;
	else if (this->GetAllMinutes() < t.GetAllMinutes())
		return -1;
	else
		return 0;
}
String Time::ToString () {
	return String(hour) + String(":") + String(minute);
}
Time Time::operator+ (const Time &t) {
	Time out;
	out.SetAllMinutes(this->GetAllMinutes() + t.GetAllMinutes());
	return out;
}
Time Time::operator- (const Time &t) {
	Time out;
	out.SetAllMinutes(this->GetAllMinutes() - t.GetAllMinutes());
	return out;
}
bool Time::operator> (const Time &t) {
	return (this->Compare(t) == 1);
}
