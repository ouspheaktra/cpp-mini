#include "string_mixed.h"

void S::Null() {
	if (ch)
		delete[] ch;
	ch = NULL;
	if (wch)
		delete[] wch;
	wch = NULL;
}

/* CONSTRUCTOR */
S::S() {
	Empty();
}
S::S(const wchar_t *s) {
	Set(s);
}
S::S(const wchar_t c) {
	Set(c);
}
S::S(const char *s) {
	Set(s);
}
S::S(double number) {
	Set(number);
}
S::S(int number) {
	Set(number);
}
// Copy
S::S(const S &s) {
	Set(s);
}

/* DESTRUCTOR */
S::~S() {
	Null();
}

void S::Set(const S & s) {
	if (isWch)
		Set(s.ToWChar());
	else
		Set(s.ToChar());
}

/* METHOD */
void S::Set(const wchar_t *s) {
	isWch = true;
	Null();
	if (s) {
		int l = wcslen(s) + 1;
		wch = new wchar_t[l];
		wcscpy(wch, s);
		
		ch = new char[l];
		wcstombs(ch, s, l);
	} else
		Empty();
}
void S::Set(const wchar_t c) {
	wchar_t n[2] = { c, 0 };
	Set(n);
}

void S::Set(const char *s) {
	isWch = false;
	Null();
	if (s) {
		int l = strlen(s) + 1;
		ch = new char[l];
		strcpy(ch, s);
		
		wch = new wchar_t[l];
		mbstowcs(wch, ch, l);
	} else
		Empty();
}

void S::Set(const char c) {
	char n[2] = { c, 0 };
	Set(n);
}

/*
void S::Set(const TCHAR *format, ...) {
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

void S::Set(double num, int decimalPoint) {
	if (isfinite(num)) {
		char format[10] = { 0 };
		snprintf(format, 10, "%%.%df", decimalPoint);
		char tmp[20] = { 0 };
		snprintf(tmp, 20, format, num);
		Set(tmp);
	} else {
		if (isnan(num))
			Set("NAN");
		else {
			if (num == INFINITY)
				Set("INFINITY");
			else
				Set("-INFINITY");
		}
	}
}
void S::Set(int num) {
	char tmp[20] = { 0 };
	snprintf(tmp, 20, "%d", num);
	Set(tmp);
}
void S::Empty() {
	Null();
	wch = new wchar_t[1];
	wch[0] = 0;
	ch = new char[1];
	ch[0] = 0;
}
int S::ToInt() const {
	return (isWch ? _wtoi(wch) : atoi(ch));
}
double S::ToDouble() const {
	return (isWch ? _wtof(wch) : atof(ch));
}
wchar_t * S::ToWChar() const {
	return wch;
}
char * S::ToChar() const {
	return ch;
}
int S::IndexOf(const S & str) const {
	int id = -1;
	if (!isWch) {
		char * found = strstr(ch, str.ToChar());
		if (found)
			id = found - ch;
	} else {
		wchar_t * found = wcsstr(wch, str.ToWChar());
		if (found)
			id = found - wch;
	}
	return id;
}
int S::Count(const S & str) const {
	int count = 0;
	int id = IndexOf(str);
	if (id >= 0)
		if (!isWch)
			return 1 + S(ch + id + str.Length()).Count(str);
		else
			return 1 + S(wch + id + str.Length()).Count(str);
	return count;
}
int S::Length() const {
	if (isWch)
		return wcslen(wch);
	else
		return strlen(ch);
}
S S::SubString(int start, int length) const {
	if (isWch) {
		wchar_t *str = new wchar_t[length + 1];
		wcsncpy(str, wch + start, length);
		str[length] = 0;
		S out(str);
		delete[] str;
		return out;
	} else {
		char *str = new char[length + 1];
		strncpy(str, ch + start, length);
		str[length] = 0;
		S out(str);
		delete[] str;
		return out;
	}
}

/* OPERATOR */
S::operator wchar_t * () const {
	return ToWChar();
}
S::operator char * () const {
	return ToChar();
}
S::operator bool() const {
	return Length();
}
wchar_t S::operator[](const int i) const {
	return (isWch ? wch[i] : ch[i]);
}
void S::operator= (const S &str) {
	Set(str);
}
bool S::operator== (const S &str) const {
	if (isWch)
		return (wcscmp(wch, str.ToWChar()) == 0);
	else
		return (strcmp(ch, str.ToChar()) == 0);
}
bool S::operator!=(const S & str) const {
	return !(*this == str);
}

S S::operator+ (const S &str) {
	if (isWch) {
		wchar_t *newStr = new wchar_t[str.Length() + Length() + 1];
		wcscpy(newStr, wch);
		wcscat(newStr, str.ToWChar());
		Set(newStr);
		delete[] newStr;
	} else {
		char *newStr = new char[str.Length() + Length() + 1];
		strcpy(newStr, ch);
		strcat(newStr, str.ToChar());
		Set(newStr);
		delete[] newStr;
	}
	return *this;
}
S & S::operator+= (const S &str) {
	*this = *this + str;
	return *this;
}
