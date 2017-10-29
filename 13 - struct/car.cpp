#include <iostream>
#include <windows.h>
#include <math.h>
using namespace std;

// car's number 		// last byte: 0=NUMBER, 1=WORD
union car_number {
	int number;
	char word[10];
};

// Car's Structure
struct car {
	char color[50];
	char model[50];
	car_number number;
};

// is provided char[] number
bool isNumber(char c[]) {
	for (int i = 0, n = strlen(c); i < n; i++)
		if (c[i] < '0' || c[i] > '9')
			return false;
	return true;
}

// return number which converted from char[]
int toNumber(char c[]) {
	int num = 0;
	for (int i = 0, n = strlen(c); i < n; i++)
		num += (short)(c[i] - '0')*pow(10, n-i-1);
	return num;
}

// string to lowercase
char *tolower(char c[]) {
	int s = strlen(c);	// length of string
	char *str = new char[s];	// to store string
	for (int i = 0; i < s; i++)	// loop each char
		str[i] = tolower(c[i]);	// lowercase each char
	str[s] = '\0';		// terminate string
	return str;	// return string with all lowercase
}

// clear screen
void clear() {
	system("cls");
}

// press any key to continue
void pause() {
	cout << endl;
	system("pause");
}

// fill car
void fill(car &c, char color[], char model[], char number[]="") {
	strcpy(c.color, color);
	strcpy(c.model, model);
	if (strlen(number)) {
		if (isNumber(number)) {
			c.number.number = toNumber(number);
			c.number.word[9] = 0;
		} else {
			strcpy(c.number.word, number);
			c.number.word[9] = 1;
		}
	}
}

// print car
void print(car c) {
	cout << c.color << " " << c.model << " with number ";
	if (c.number.word[9] == 0)
		cout << c.number.number;
	else
		cout << c.number.word;
	cout << endl;
}

// print all cars
void print(car c[], int size) {
	for (int i = 0; i < size; i++)
		print(c[i]);
}

// search car
void search(car c[], int size) {
	char input[25];
	cout << "Input Car's Number: "; cin >> input;
	cout << endl;
	if (isNumber(input)) {
		for (int i = 0; i < size; i++) {
			if (c[i].number.number == toNumber(input)) {
				print(c[i]);
				return;
			}
		}
	} else {
		for (int i = 0; i < size; i++) {
			if (strcmp(tolower(c[i].number.word), tolower(input)) == 0) {
				print(c[i]);
				return;
			}
		}
	}
	cout << "NOT FOUND\n";
}

// edit one car
void edit(car &c) {
	cout << "Old Record:\n"; print(c); cout << endl;
	cout << "1. Edit Color" << endl;
	cout << "2. Edit Model" << endl;
	cout << "3. Edit Number" << endl;
	cout << "0. GO BACK" << endl << endl;
	int num;
	while(1) {
		cout << "Choose: "; cin >> num;
		if (num == 0) break;
		if (num >= 1 && num <= 3) {
			char input[50];
			cout << endl << "Input: "; cin >> input;
			switch (num) {
				case 1: fill(c, input, c.model); break;
				case 2: fill(c, c.color, input); break;
				case 3: fill(c, c.color, c.model, input);
				default: break;
			}
			cout << endl << "New Record:" << endl; print(c);
			return;
		}
	}
}

// edit option
void edit(car c[], int size) {
	for (int i = 1; i <= size; i++) {
		cout << i << ". ";
		print(c[i-1]);
	}
	cout << "0. GO BACK" << endl << endl;
	int num;
	while (1) {
		cout << "Choose: "; cin >> num;
		if (num == 0) break;
		if (num >= 1 && num <= size) {
			clear();
			edit(c[num-1]);
			return;
		}
	}
}

main() {
	const int size = 8;
	car cars[size];
	fill(cars[0], "Black", "Tesla", "95124");
	fill(cars[1], "Red", "Mazda", "65484");
	fill(cars[2], "Blue", "Lexus", "ASDFAE");
	fill(cars[3], "Red", "Camery", "13254");
	fill(cars[4], "White", "Camery", "ZXCVHJKL");
	fill(cars[5], "Black", "Tesla", "84567");
	fill(cars[6], "White", "Mazda", "QWERTYUI");
	fill(cars[7], "Blue", "Tesla", "98754");
	
	void (*operation[])(car c[], int size) = {print, search, edit};
	int num;
	
	while (1) {
		clear();
		cout << "1 - Print\n";
		cout << "2 - Search by Number\n";
		cout << "3 - Edit\n";
		cout << "0 - EXIT\n\n";
		cout << "Choose: "; cin >> num;
		if (num == 0) break;
		if (num >= 1 && num <= 3) {
			clear();
			(*operation[num-1])(cars, size);
			pause();
		}
	}
	cout << "\nThank you for using our Service.";
}
