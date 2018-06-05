#include <iostream>
#include <string.h>
using namespace std;

class Man {
	char * name = NULL;
	bool male;
public:
	Man(const char * name, bool isMale) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		male = isMale;
	}
	Man(const Man &m) {
		this->name = new char[strlen(m.name) + 1];
		strcpy(this->name, m.name);
		male = m.male;
	}
	~Man() {
		if (name)
			delete [] name;
	}
	
	void Cout() {
		cout << "\t\t" << name << ": " << (male ? "male" : "female") << endl;
	}
};

class Apartment {
	Man **value = NULL;
	int size;
public:
	Apartment() {
		value = NULL;
		size = 0;
	}
	~Apartment() {
		if (value) {
			for (int i = 0; i < size; i++)
				delete value[i];
			delete [] value;
		}
	}
	
	void AddMan(const Man &man) {
		AddMan(new Man(man));
	}
	void AddMan(Man &man) {
		AddMan(&man);
	}
	void AddMan(Man *man) {
		Man **tmp = value;
		value = new Man*[size + 1];
		for (int i = 0; i < size; i++)
			value[i] = tmp[i];
		value[size++] = man;
		if (tmp)
			delete [] tmp;
	}
	void Cout() {
		cout << "\tApartment:" << endl;
		for (int i = 0; i < size; i++)
			value[i]->Cout();
	}
	
	Man &operator[] (int i) {
		return *value[i];
	}
};

class House {
	Apartment **value = NULL;
	int size;
public:
	House() {
		value = NULL;
		size = 0;
	}
	~House() {
		if (value) {
			for (int i = 0; i < size; i++)
				delete value[i];
			delete [] value;	
		}
	}
	
	void AddApartment(Apartment &apartment) {
		AddApartment(&apartment);
	}
	void AddApartment(Apartment *apartment) {
		Apartment **tmp = value;
		value = new Apartment*[size + 1];
		for (int i = 0; i < size; i++)
			value[i] = tmp[i];
		value[size++] = apartment;
		if (tmp)
			delete [] tmp;
	}
	void Cout() {
		cout << "House:" << endl;
		for (int i = 0; i < size; i++)
			value[i]->Cout();
	}
	
	Apartment &operator[] (int i) {
		return *value[i];
	}
};


int main() {
	Man m1("ouspheaktra", true);
	Apartment a1;
	a1.AddMan(m1);
	a1.AddMan(Man("kimly", true));
	a1.AddMan(new Man("daveat", true));
	
	Apartment a2;
	a2.AddMan(Man("dara", true));
	a2.AddMan(Man("kimhorn", false));
	a2.AddMan(new Man("veha", true));
	
	House h;
	h.AddApartment(a1);
	h.AddApartment(a2);
	h.Cout();
}
