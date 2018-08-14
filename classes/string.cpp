#include "string.h"

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
	if (isWch) {
		wchar_t * str = s.ToWChar();
		Set(str);
		delete[] str;
	} else {
		char * str = s.ToChar();
		Set(str);
		delete[] str;
	}
}

/* METHOD */
void S::Set(const wchar_t *s) {
	isWch = true;
	Null();
	if (s) {
		wch = new wchar_t[wcslen(s) + 1];
		wcscpy(wch, s);
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
		ch = new char[strlen(s) + 1];
		strcpy(ch, s);
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
	if (isWch) {
		wch = new wchar_t[1];
		wch[0] = 0;
	} else {
		ch = new char[1];
		ch[0] = 0;
	}
}
int S::ToInt() const {
	return (isWch ? _wtoi(wch) : atoi(ch));
}
double S::ToDouble() const {
	return (isWch ? _wtof(wch) : atof(ch));
}
wchar_t * S::ToWChar() const {
	wchar_t * out = new wchar_t[Length() + 1];
	if (isWch)
		wcscpy(out, wch);
	else
		mbstowcs(out, ch, Length() + 1);
	return out;
}
char * S::ToChar() const {
	char * out = new char[Length() + 1];
	if (!isWch)
		strcpy(out, ch);
	else
		wcstombs(out, wch, Length() + 1);
	return out;
}
int S::IndexOf(const S & str) const {
	int id = -1;
	if (!isWch) {
		char * word = str.ToChar();
		char * found = strstr(ch, word);
		if (found)
			id = found - ch;
		delete[] word;
	} else {
		wchar_t * word = str.ToWChar();
		wchar_t * found = wcsstr(wch, word);
		if (found)
			id = found - wch;
		delete[] word;
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
S::operator char*() const {
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
	if (isWch) {
		wchar_t *otherStr = str.ToWChar();
		bool out = (wcscmp(wch, otherStr) == 0);
		delete[] otherStr;
		return out;
	} else {
		char *otherStr = str.ToChar();
		bool out = (strcmp(ch, otherStr) == 0);
		delete[] otherStr;
		return out;
	}
}
bool S::operator!=(const S & str) const {
	return !(*this == str);
}

S & S::operator+ (const S &str) {
	if (isWch) {
		wchar_t *newStr = new wchar_t[str.Length() + Length() + 1];
		wchar_t *otherStr = str.ToWChar();
		wcscpy(newStr, wch);
		wcscat(newStr, otherStr);
		Set(newStr);
		delete[] newStr;
		delete[] otherStr;
	} else {
		char *newStr = new char[str.Length() + Length() + 1];
		char *otherStr = str.ToChar();
		strcpy(newStr, ch);
		strcat(newStr, otherStr);
		Set(newStr);
		delete[] newStr;
		delete[] otherStr;
	}
	return *this;
}
S & S::operator+= (const S &str) {
	*this = *this + str;
	return *this;
}