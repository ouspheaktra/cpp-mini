#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <stdarg.h>
#include "string.h"

/* CONSTRUCTOR */
String::String() {
	Empty();
}
String::String(const TCHAR *s) {
	SetValue(s);
}
#ifdef _UNICODE
String::String(const char *s) {
	SetValue(s);
}
#endif
String::String(double number) {
	SetValue(number);
}
String::String(int number) {
	SetValue(number);
}
// Copy
String::String(const String &s) {
	SetValue(s.value);
}

/* DESTRUCTOR */
String::~String() {
	if (value)
		delete[] value;
}

/* METHOD */
void String::SetValue(const TCHAR *s) {
	if (value)
		delete [] value;
	if (s) {
		value = new TCHAR[_tcslen(s) + 1];
		_tcscpy(value, s);
	}
	else
		Empty();
}
#ifdef _UNICODE
void String::SetValue(const char *s) {
	int len = (int)strlen(s) + 1;
	TCHAR *t = new TCHAR[len];
	for (int i = 0; i < len; i++)
		t[i] = s[i];
	SetValue(t);
	delete[] t;
}
#endif
/*
void String::SetValue(const TCHAR *format, ...) {
	va_list list;
	va_start(list, format);
	for (int i = 0, n = strlen(format); i < n; i++) {
		if (format[i] == '%') {
			switch (format[i+1]) {
				case 'd':	cout << va_arg(list, int);		break;
				case 's':	cout << va_arg(list, TCHAR *);	break;
			}
			i++;
		} else
			cout << format[i];
	}
	va_end(list);
}
*/
void String::SetValue(double num) {
	if (isfinite(num)) {
		TCHAR tmp[20] = { '\0' };
		_sntprintf(tmp, 20, _TEXT("%.2f"), num);
		SetValue(tmp);
	} else {
		if (isnan(num))
			SetValue("NAN");
		else {
			if (num == INFINITY)
				SetValue("INFINITY");
			else
				SetValue("-INFINITY");
		}
	}
}
void String::SetValue(int num) {
	TCHAR tmp[20] = {'\0'};
	_sntprintf(tmp, 20, _TEXT("%d"), num);
	SetValue(tmp);
}
void String::Empty() {
	if (value != NULL)
		delete [] value;
	value = new TCHAR[1];
	value[0] = '\0';
}
int String::ToInt() {
	return _ttoi(value);
}
double String::ToDouble() {
	return _tstof(value);
}
void String::Cin() {
	char s[256];
	std::cin.getline(s, 256);
	SetValue(s);
}
const TCHAR * String::GetValue() {
	return value;
}
#ifdef _UNICODE
const TCHAR * String::ToTCHAR() {
	return value;
}
const char * String::ToChar() {
	if (sizeof(TCHAR) == sizeof(char))
		return (char *)value;
	char *out = new char[Length() + 1];
	wcstombs(out, value, Length() + 1);
	return out;
}
#else
const char * String::ToChar() {
	return value;
}
#endif
int String::Find(const String & str) {
	TCHAR * found = _tcsstr(value, str.value);
	if (found)
		return (found - value);
	return -1;
}
int String::Length() {
	return _tcslen(value);
}
String String::SubString(int start, int length) {
	TCHAR *str = new TCHAR[length + 1];
	for (int i = 0; i < length; i++)
		str[i] = value[start+i];
	str[length] = '\0';
	return String(str);
}
/*
String::operator char*() {
	char *out = new char[Length() + 1];
	for (int i = 0, n = Length() + 1; i < n; i++)
		out[i] = value[i];
	return out;
}
*/
/* OPERATOR */
String::operator TCHAR* () {
	return value;
}
String::operator bool() {
	return !(*this == String(""));
}
void String::operator= (const String &str) {
	SetValue(str.value);
}
bool String::operator== (const String &str) {
	return (_tcscmp(value, str.value) == 0);
}

bool String::operator!=(const String & str) {
	return !(*this == str);
}

String String::operator+ (const String &str) {
	TCHAR *newstr = new TCHAR[_tcslen(str.value) + _tcslen(value) + 1];
	_tcscpy(newstr, value);
	_tcscat(newstr, str.value);
	return String(newstr);
}
String String::operator+= (const String &str) {
	*this = *this + str;
	return *this;
}
/*
String String::operator- (const String &str) {
	TCHAR out[_tcslen(value) + 1] = {'\0'};
	TCHAR *start = value;
	TCHAR *pos;
	TCHAR tmp[_tcslen(value) + 1];
	while (pos = _tcsstr(start, str.value)) {
		strncpy(tmp, start, pos - start);
		tmp[pos - start] = '\0';
		_tcscat(out, tmp);
		start = pos + _tcslen(str.value);
	}
	_tcscat(out, start);
	return String(out);
}
String String::operator* (const String &str) {
	TCHAR out[std::min(_tcslen(str.value), _tcslen(value)) + 1] = {'\0'};
	for (int i = 0, l = 0, n = _tcslen(value); i < n; i++)
		if (strchr(str.value, value[i]) && !_tcschr(out, value[i])) {
			out[l] = value[i];
			out[l++ + 1] = '\0';
		}
	return String(out);
}
String String::operator/ (const String &str) {
	TCHAR out[_tcslen(str.value) + _tcslen(value) + 1];
	int l = 0;
	for (int i = 0, n = _tcslen(value); i < n; i++)
		if (!_tcschr(str.value, value[i]))
			out[l++] = value[i];
	for (int i = 0, n = _tcslen(str.value); i < n; i++)
		if (!_tcschr(value, str.value[i]))
			out[l++] = str.value[i];
	out[l] = '\0';
	return String(out);
}

int main() {
	cout << "yes";
}
*/
