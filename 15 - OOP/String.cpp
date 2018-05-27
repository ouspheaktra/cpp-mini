#include <iostream>
#include <string.h>
using namespace std;

class String {
	char *value = NULL;
	static unsigned int instances;
	public:
	String() {
		value = new char[80];
		instances++;
	}
	String(const char *s) {
		value = new char[strlen(s) + 1];
		strcpy(value, s);
		instances++;
	}
	String(const char *s, unsigned int size) {
		value = new char[size];
		strcpy(value, s);
		instances++;
	}
	void Input() {
		cin >> value;
	}
	char * GetValue() {
		return value;
	}
	static unsigned int GetInstancesNumber() {
		return instances;
	}
	~String() {
		if (value) delete [] value;
	}
};
unsigned int String::instances = 0;

int main() {
	String s0;
	s0.Input();
	String s1("one");
	String s2("twozdfedfsesadfasdf", 1);
	cout << s0.GetValue() << " " << s1.GetValue() << " " << s2.GetValue() << " " << String::GetInstancesNumber();
}
