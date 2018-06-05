#include <iostream>
#include <stdarg.h>
using namespace std;

class List {
	int *value = NULL;
	int size;
public:
	/* CONSTRUCTOR */
	List() {
		size = 0;
		value = new int[size];
	}
	List(int size, bool *n) {
		this->size = size;
		value = new int[size];
		SetAllTo(0);
	}
	List(int size, ...) {
		this->size = size;
		value = new int[size];
		va_list args;
		va_start(args, size);
		for (int i = 0; i < size; i++)
			value[i] = va_arg(args, int);
		va_end(args);
	}
	// copy
	List(const List &l) {
		(*this) = l;		
	}
	// destructor
	~List() {
		if (value)
			delete [] value;
	}

	/* METHOD */
	void SetAllTo(int num) {
		for (int i = 0; i < size; i++)
			value[i] = num;
	}
	int IndexOf(int num) const {
		for (int i = 0; i < size; i++)
			if (num == value[i])
				return i;
		return -1;
	}
	bool Contains(int num) const {
		return (IndexOf(num) >= 0);
	}
	void Cout() {
		cout << "size: " << size << endl;
		for (int i = 0; i < size; i++)
			cout << i << ": " << value[i] << endl;
	}

	/* OPERATOR */
	int &operator[] (int i) {
		return value[i];
	}
	void operator= (const List &l) {
		size = l.size;
		if (value)
			delete [] value;
		value = new int[size];
		for (int i = 0; i < size; i++)
			value[i] = l.value[i];
	}
	void operator+= (const List &l) {
		*this = *this + l;
	}
	void operator-= (const List &l) {
		*this = *this - l;
	}
	List operator+ (const List &l) {
		List out(size + l.size);
		for (int i = 0; i < size; i++)
			out[i] = value[i];
		for (int i = 0; i < l.size; i++)
			out[i+size] = l.value[i];
		return out;
	}
	List operator- (const List &l) {
		int num[size];
		int nSize = 0;
		for (int i = 0; i < size; i++)
			if (!l.Contains(value[i]))
				num[nSize++] = value[i];
		List out(nSize);
		for (int i = 0; i < nSize; i++)
			out[i] = num[i];
		return out;
	}
};

int main() {
	List l = List(5, 12, 32, 15, 57, 6) - List(2, 32, 57);
	l.Cout();
}
