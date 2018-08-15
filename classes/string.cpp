#include "string.h"

void S::Null() {
	if (value)
		delete[] value;
	value = NULL;
}

/* CONSTRUCTOR */
S::S() {
	Set(NULL);
}
S::S(const TCHAR *s) {
	Set(s);
}
S::S(const TCHAR c) {
	Set(c);
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
	Set(s.value);
}

/* METHOD */
void S::Set(const TCHAR *s) {
	Null();
	if (s) {
		value = new TCHAR[_tcslen(s) + 1];
		_tcscpy(value, s);
	} else
		Empty();
}
void S::Set(const TCHAR c) {
	TCHAR n[2] = { c, 0 };
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
		TCHAR format[10] = { 0 };
		_sntprintf(format, 10, _TEXT("%%.%df"), decimalPoint);
		TCHAR tmp[20] = { 0 };
		_sntprintf(tmp, 20, format, num);
		Set(tmp);
	} else {
		if (isnan(num))
			Set(_TEXT("NAN"));
		else {
			if (num == INFINITY)
				Set(_TEXT("INFINITY"));
			else
				Set(_TEXT("-INFINITY"));
		}
	}
}
void S::Set(int num) {
	TCHAR tmp[20] = { 0 };
	_sntprintf(tmp, 20, _TEXT("%d"), num);
	Set(tmp);
}
void S::Empty() {
	Null();
	value = new TCHAR[1];
	value[0] = 0;
}
int S::ToInt() const {
	return _ttoi(value);
}
double S::ToDouble() const {
	return _ttof(value);
}
const TCHAR * S::GetValue() const {
	return value;
}

int S::IndexOf(const S & str) const {
	int id = -1;
	TCHAR * found = wcsstr(value, str.value);
	if (found)
		id = found - value;
	return id;
}
int S::Count(const S & str) const {
	int count = 0;
	int id = IndexOf(str);
	if (id >= 0)
		return 1 + S(value + id + str.Length()).Count(str);
	return count;
}
int S::Length() const {
	return _tcslen(value);
}
S S::SubString(int start, int length) const {
	TCHAR *str = new TCHAR[length + 1];
	_tcsncpy(str, value + start, length);
	str[length] = 0;
	S out(str);
	delete[] str;
	return out;
}

/* OPERATOR */
S::operator const TCHAR * () const {
	return GetValue();
}
S::operator bool() const {
	return Length();
}
TCHAR S::operator[](const int i) const {
	return value[i];
}
void S::operator= (const S &str) {
	Set(str);
}
bool S::operator== (const S &str) const {
	return (_tcscmp(value, str.value) == 0);
}
bool S::operator!=(const S & str) const {
	return !(*this == str);
}

S S::operator+ (const S &str) {
	TCHAR *newStr = new TCHAR[str.Length() + Length() + 1];
	_tcscpy(newStr, value);
	_tcscat(newStr, str.value);
	Set(newStr);
	delete[] newStr;
	return *this;
}
S & S::operator+= (const S &str) {
	*this = *this + str;
	return *this;
}

#ifdef _UNICODE
S::S(const char * s) {
	Set(s);
}
S::S(const char c) {
	Set(c);
}
void S::Set(const char * s) {
	TCHAR * str = new TCHAR[strlen(s) + 1];
	mbstowcs(str, s, strlen(s) + 1);
	Set(str);
	delete[] str;
}

void S::Set(const char c) {
	char str[2] = { c, 0 };
	Set(str);
}
const char * S::ToChar() const {
	char * out = new char[Length() + 1];
	wcstombs(out, value, Length() + 1);
	return out;
}
S::operator const char*() const {
	return ToChar();
}
#endif