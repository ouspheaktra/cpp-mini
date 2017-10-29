#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

// header is a new datatype represent column name
enum header {
	Name,
	Phone
};
// column name as string
string header_string[] = {
	"name",
	"phone number"
};

int row = 0;
const short col = 2;
char ***list = NULL;

// allocate memory for list
char ***allocate_memory(int row, int col) {
	char ***arr = new char**[row];
	for (int i = 0; i < row; i++) {
		arr[i] = new char*[col];
		for (int j = 0; j < col; j++)
			arr[i][j] = new char[100];
	}
	return arr;
}
// remove entire list
void remove_list() {
	if (list == NULL) return;
	for (int i = 0; i < row; i++)
		delete[](list)[i];
	delete[]list;
	list = NULL;
}
// pause console
void pause() {
	cout << endl;
	system("pause");
}
// clear console
void clear() {
	system("cls");
}

// give the option to the user
int option() {
	clear();
	cout << "1 - display" << endl
		<< "2 - search" << endl
		<< "3 - add" << endl
		<< "4 - modify" << endl
		<< "5 - delete" << endl
		<< "0 - EXIT" << endl;
	int num;
	cout << "\nChoose : ";
	cin >> num;
	return (num < 0 || num > 5) ? option() : num;
}

// display all row
void display() {
	clear();
	cout << "Name\t\tPhone Number" << endl << "---" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			cout << list[i][j] << "\t";
		cout << endl;
	}
	pause();
}
// display specific row
void display_row(int index) {
	cout << "Name\t\tPhone Number" << endl << "---" << endl;
	for (int j = 0; j < col; j++)
		cout << list[index][j] << "\t";
	cout << endl;
}

// add input
void add() {
	clear();
	// create temp to store temmporary new list
	char ***temp = allocate_memory(row+1, col);
	// copy old list to temp
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			temp[i][j] = list[i][j];
	// remove old list and point to temp
	remove_list();
	list = temp;
	
	// input new row and insert it into last row of list
	cout << "Input Name : "; cin >> list[row][Name];
	cout << "Input Phone Number : "; cin >> list[row][Phone];
	row++;
	pause();
}

// search word in any column, return id of row
int search(header col, char *word) {
	for (int i = 0; i < row; i++)
		if (strcmp(list[i][col], word) == 0)
			return i;
	return -1;
}
// search any column (interface)
void search(header col) {
	clear();
	cout << "Input a " << header_string[col] << " to search : ";
	// input name
	char *name = new char[100];
	cin >> name;
	// search name
	int search_result = search(col, name);
	cout << "\n";
	// if not exist
	if (search_result == -1)	cout << "NOT FOUND\n";
	// if exist
	else						display_row(search_result);
	pause();
}
// search option
void search() {
	clear();
	cout << "Search\n";
	cout << "1 - by Name\n";
	cout << "2 - by Phone Number\n";
	cout << "0 - BACK\n";
	cout << "\nChoose : ";
	int num;
	cin >> num;
	switch (num) {
		case 0: return;
		case 1: search(Name); break;
		case 2: search(Phone); break;
		default: search();
	}
}

// modify row (interface)
void modify(header col) {
	clear();
	// ask to input old one
	cout << "Input old " << header_string[col] << ": ";
	char *old = new char[100];
	cin >> old;
	// search if old one exist
	int search_result = search(col, old);
	cout << "\n";
	// if not exist, show message, ask again
	if (search_result == -1) {
		cout << "Old ... NOT FOUND\n";
		pause();
		modify(col);
	// if exist
	} else {
		// ask to input new one
		cout << "Input new " << header_string[col] << ": ";
		char *neww = new char[100];
		cin >> neww;
		// delete old one
		delete[] list[search_result][col];
		// point column of found row to new one
		list[search_result][col] = neww;
		cout << "\nName is changed successfully\n";
		pause();
	}
}
// modify option
void modify() {
	clear();
	cout << "Modify\n";
	cout << "1 - Name\n";
	cout << "2 - Phone\n";
	cout << "0 - BACK\n";
	cout << "\nChoose : ";
	int num;
	cin >> num;
	switch (num) {
		case 0: return;
		case 1: modify(Name); break;
		case 2: modify(Phone); break;
		default: modify();
	}
}

// delete row by index
void del(int index) {
	// create temporary list
	char ***temp = new char**[row-1];
	// copy from list to temp, except the one that needs to be deleted
	for (int i = 0; i < row-1; i++) {
		if (i < index)	temp[i] = list[i];
		else			temp[i] = list[i+1];
	}
	// delete the wanted one
	delete[]list[index];
	// point list to temp
	list = temp;
	row--;
	cout << "Successful delete\n";
}
// delete any column (interface)
void del(header col) {
	clear();
	// ask ... to delete
	cout << "Input a " << header_string[col] << " to delete : ";
	char *name = new char[100];
	cin >> name;
	// search provided input in the list
	int search_result = search(col, name);
	cout << "\n";
	// if it's not in the list
	if (search_result == -1)	cout << "NOT FOUND";
	// if it is, delete
	else						del(search_result);
	pause();
}
// delete option
void del() {
	clear();
	cout << "Delete\n";
	cout << "1 - By Name\n";
	cout << "2 - By Phone\n";
	cout << "0 - BACK\n";
	cout << "\nChoose : ";
	int num;
	cin >> num;
	switch (num) {
		case 0: return;
		case 1: del(Name); break;
		case 2: del(Phone); break;
		default: del();
	}
}

int main() {
	int number;
	while (1) {
		number = option();
		if (number == 0) break;
		void (*operation[])() = {display, search, add, modify, del};
		(*operation[number-1])();
	}
	cout << "\nThanks for using our services.";
}
