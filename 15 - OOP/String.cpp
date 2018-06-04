#include <iostream>
#include <string.h>
using namespace std;

class String {
	char *value = NULL;
public:
	/* CONSTRUCTOR */
	String() {
		value = new char[80];
		value[0] = '\0';
	}
	String(char c) {
		value = new char[2];
		value[0] = c;
		value[1] = '\0';
	}
	String(const char *s) {
		SetValue(s);
	}
	String(const String &s) {
		SetValue(s.value);
	}
	
	/* DESTRUCTOR */
	~String() {
		SetValue(NULL);
	}
	
	/* METHOD */
	void SetValue(const char *s) {
		if (value)
			delete [] value;
		if (s) {
			value = new char[strlen(s) + 1];
			strcpy(value, s);
		} else
			value = NULL;
	}
	void Cin() {
		char s[256];
		cin.getline(s, 256);
		SetValue(s);
	}
	const char * GetValue() {
		return value;
	}
	int Length() {
		return strlen(value);
	}
	String SubString(int start, int length) {
		char *str = new char[length + 1];
		for (int i = 0; i < length; i++)
			str[i] = value[start+i];
		str[length] = '\0';
		return String(str);
	}
	
	/* OPERATOR */
	operator char*() {
		return value;
	}
	bool operator== (String &str) {
		return (strcmp(value, str.value) == 0);
	}
	String operator+ (const String &str) {
		char newstr[strlen(str.value) + strlen(value) + 1];
		strcpy(newstr, value);
		strcat(newstr, str.value);
		return String(newstr);
	}
	String operator- (const String &str) {
		char *out = new char[strlen(value) + 1];
		out[0] = '\0';
		char *start = value;
		char *pos;
		while (1) {
			pos = strstr(start, str.value);
			if (pos) {
				strcat(out, String(start).SubString(0, pos - start));
				//if (po + strlen(str.value) < str + strlen(str))
					start = pos + strlen(str.value);
			} else {
				strcat(out, start);
				break;
			}
			
		};
		return String(out);
	}
	String operator* (const String &str) {
		char out[max(strlen(str.value), strlen(value)) + 1];
		int l = 0;
		out[0] = '\0';
		for (int i = 0, n = strlen(value); i < n; i++) {
			if (strchr(str.value, value[i]) && !strchr(out, value[i])) {
				out[l] = value[i];
				out[l+1] = '\0';
				l++;
			}
		}
		return String(out);
	}
	String operator/ (const String &str) {
		char out[max(strlen(str.value), strlen(value)) + 1];
		char l = 0;
		for (int i = 0, n = strlen(value); i < n; i++)
			if (!strchr(str.value, value[i]))
				out[l++] = value[i];
		for (int i = 0, n = strlen(str.value); i < n; i++)
			if (!strchr(value, str.value[i]))
				out[l++] = str.value[i];
		out[l] = '\0';
		return String(out);
	}
};

int main () {
  cout << String("helolo asdf aslo asdf sd") - String("lo");
}
