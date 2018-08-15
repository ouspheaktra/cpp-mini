#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <math.h>

class S {
	TCHAR *value = NULL;
	void Null();
public:
	/* CONSTRUCTOR */
	S();
	S(const TCHAR *s);
	S(const TCHAR c);
	S(double number);
	S(int number);
	// Copy
	S(const S &s);
	
	/* DESTRUCTOR */
	~S();
	
	/* METHOD */
	void Set(const S &s);
	void Set(const TCHAR *s);
	void Set(const TCHAR c);
	void Set(double num, int decimalPoint=2);
	void Set(int num);
	void Empty();

	int ToInt() const;
	double ToDouble() const;
	const TCHAR * GetValue() const;

	int IndexOf(const S &str) const;
	int Count(const S &str) const;
	int Length() const;

	S SubString(int start, int length) const;
	
	/* OPERATOR */
	operator const TCHAR * () const;
	operator bool() const;
	TCHAR operator[] (const int i) const;
	void operator= (const S &str);
	bool operator== (const S &str) const;
	bool operator!= (const S &str) const;
	S operator+ (const S &str);
	S & operator+= (const S &str);

#ifdef _UNICODE
	S(const char *s);
	S(const char c);
	void Set(const char *s);
	void Set(const char c);
	const char * ToChar() const;
	operator const char * () const;
#endif
};

typedef S String;

#endif