#include <stdlib.h>
#include <iostream>
#include <tchar.h>
#include <stdarg.h>
#include "string.h"

/* CONSTRUCTOR */
String::String() {
	value = new TCHAR[80];
	value[0] = '\0';
}
String::String(const TCHAR *s) {
	SetValue(s);
}
String::String(const char *s) {
	SetValue(s);
}
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
	SetValue(NULL);
}

/* METHOD */
void String::SetValue(const TCHAR *s) {
	if (value)
		delete [] value;
	if (s) {
		value = new TCHAR[_tcslen(s) + 1];
		_tcscpy(value, s);
	} else
		value = NULL;
}
void String::SetValue(const char *s) {
	int len = strlen(s) + 1;
	TCHAR *t = new TCHAR[len];
	for (int i = 0; i < len; i++)
		t[i] = s[i];
	SetValue(t);
	delete[] t;
}
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
	TCHAR tmp[20] = {'\0'};
	_stprintf(tmp, _TEXT("%f"), num);
	SetValue(tmp);
}
void String::SetValue(int num) {
	TCHAR tmp[20] = {'\0'};
	_stprintf(tmp, _TEXT("%d"), num);
	SetValue(tmp);
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

/* OPERATOR */
String::operator TCHAR* () {
	return value;
}
void String::operator= (const String &str) {
	SetValue(str.value);
}
bool String::operator== (const String &str) {
	return (_tcscmp(value, str.value) == 0);
}

String String::operator+ (const String &str) {
	TCHAR *newstr = new TCHAR[_tcslen(str.value) + _tcslen(value) + 1];
	_tcscpy(newstr, value);
	_tcscat(newstr, str.value);
	return String(newstr);
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
