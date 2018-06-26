#ifndef STRING_H
#define STRING_H

#include <tchar.h>

class String {
	TCHAR *value = NULL;
public:
	/* CONSTRUCTOR */
	String();
	String(const TCHAR *s);
	String(double number);
	String(int number);
	// Copy
	String(const String &s);
	
	/* DESTRUCTOR */
	~String();
	
	/* METHOD */
	void SetValue(const TCHAR *s);
	void SetValue(double num);
	void SetValue(int num);
	int ToInt();
	double ToDouble();
	void Cin();
	const TCHAR * GetValue();
	int Length();
	String SubString(int start, int length);
	
	/* OPERATOR */
	operator TCHAR* ();
	void operator= (const String &str);
	bool operator== (const String &str);
	String operator+ (const String &str);
	String operator- (const String &str);
	String operator* (const String &str);
	String operator/ (const String &str);
};
#endif
