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
	String(double number);
	String(int number);
	// Copy
	String(const String &s);
	
	/* DESTRUCTOR */
	~String();
	
	/* METHOD */
	void SetValue(const TCHAR *s);
#ifdef _UNICODE
	void SetValue(const char *s);
#endif
	void SetValue(double num);
	void SetValue(int num);
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
	int Find(const String &str);
	int Length();
	String SubString(int start, int length);
	
	/* OPERATOR */
	operator TCHAR* ();
	operator bool();
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
