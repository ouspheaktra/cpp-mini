#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <math.h>

class S {
	char *ch = NULL;
	wchar_t *wch = NULL;
	bool isWch = false;
	void Null();
public:
	/* CONSTRUCTOR */
	S();
	S(const char *s);
	S(const wchar_t *s);
	S(const char c);
	S(const wchar_t c);
	S(double number);
	S(int number);
	// Copy
	S(const S &s);
	
	/* DESTRUCTOR */
	~S();
	
	/* METHOD */
	void Set(const S &s);
	void Set(const wchar_t *s);
	void Set(const wchar_t c);
	void Set(const char *s);
	void Set(const char c);
	void Set(double num, int decimalPoint=2);
	void Set(int num);
	void Empty();

	int ToInt() const;
	double ToDouble() const;
	wchar_t * ToWChar() const;
	char * ToChar() const;

	int IndexOf(const S &str) const;
	int Count(const S &str) const;
	int Length() const;

	S SubString(int start, int length) const;
	
	/* OPERATOR */
	operator char * () const;
	operator wchar_t * () const;
	operator bool() const;
	wchar_t operator[] (const int i) const;
	void operator= (const S &str);
	bool operator== (const S &str) const;
	bool operator!= (const S &str) const;
	S & operator+ (const S &str);
	S & operator+= (const S &str);
};

typedef S String;

#endif