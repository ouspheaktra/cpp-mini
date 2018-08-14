#ifndef STRING_H
#define STRING_H

#include <tchar.h>

class String {
	TCHAR *value = NULL;
public:
	/* CONSTRUCTOR */
	String();
#ifdef _UNICODE
	String(const char *s);
#endif
	String(const TCHAR *s);
	String(const TCHAR c);
	String(double number);
	String(int number);
	// Copy
	String(const String &s);
	
	/* DESTRUCTOR */
	~String();
	
	/* METHOD */
	void Set(const TCHAR *s);
	void Set(const TCHAR c);
#ifdef _UNICODE
	void Set(const char *s);
#endif
	void Set(double num);
	void Set(int num);
	void Empty();
	int ToInt();
	double ToDouble();
	void Cin();
	const TCHAR * GetValue();
#ifdef _UNICODE
	const TCHAR * ToTCHAR();
	const char * ToChar();
#else
	const char * ToChar();
#endif
	int IndexOf(const String &str) const;
	int Count(const String &str) const;
	const int Length() const;
	String SubString(int start, int length);
	
	/* OPERATOR */
	operator TCHAR* ();
	operator bool();
	TCHAR operator[] (const int i);
	void operator= (const String &str);
	bool operator== (const String &str);
	bool operator!= (const String &str);
	String operator+ (const String &str);
	String operator- (const String &str);
	String operator* (const String &str);
	String operator/ (const String &str);
	String operator+= (const String &str);
};
#endif
