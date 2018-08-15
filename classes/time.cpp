#include "time.h"

const String Date::Day[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

Date::Date() {
	SetDate(0, 0, 0);
}
Date::Date(int date, int month, int year) {
	SetDate(date, month, year);
}

void Date::SetNow() {
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	this->day = timeinfo->tm_wday;
	this->date = timeinfo->tm_mday;
	this->month = timeinfo->tm_mon;
	this->year = timeinfo->tm_year;
}

void Date::SetDate(int date, int month, int year) {
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_mday = date;
	timeinfo->tm_mon = month;
	timeinfo->tm_year = year;
	mktime(timeinfo);
	this->day = timeinfo->tm_wday;
	this->date = timeinfo->tm_mday;
	this->month = timeinfo->tm_mon;
	this->year = timeinfo->tm_year;
}

int Date::GetDay() {
	return day;
}

int Date::GetDate() {
	return date;
}

int Date::GetMonth() {
	return month;
}

int Date::GetYear() {
	return 1900 + year;
}

String Date::ToString() {
	return String(Day[day]) + String(" ") + String(day) + String("/") + String(month) + String("/") + String(GetYear());
}



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
void Time::SetAllSeconds(int second) {
	this->hour = second / 60 / 60;
	this->minute = second / 60 % 60;
	this->second = second % 60;
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
	return String(hour) + String(":") + String(minute) + String(":") + String(second);
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
