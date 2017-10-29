#include <iostream>
#include <windows.h>
using namespace std;

// Book's Structure
struct book {
	char title[50];
	char author[50];
};

// in Library
const int size = 10;
book books[size] = {
	{"King Lear", "William Shakespeare"},
	{"A Land of Our Own", "Golda Meir"},
	{"Non-Violent Resistance", "Mahatma Gandhi"},
	{"This is Our Strength", "Golda Meir"},
	{"The Words of Gandhi", "Mahatma Gandhi"},
	{"As You Like It", "William Shakespeare"},
	{"The Way to God", "Mahatma Gandhi"},
	{"Romeo and Juliet", "William Shakespeare"},
	{"My Life", "Golda Meir"},
	{"Key to Health", "Mahatma Gandhi"}
};

// clear screen
void clear() {
	system("cls");
}

// press any key to continue
void pause() {
	cout << endl;
	system("pause");
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

// main option, return the number the user chose
int option() {
	clear();
	// display option
	cout << "1 - Print\n";
	cout << "2 - Search\n";
	cout << "3 - Edit\n";
	cout << "4 - Sort\n";
	cout << "0 - EXIT\n\n";
	// ask to input
	int num;
	cout << "Choose: "; cin >> num;
	// return a valid choice or choose again
	return (num < 0 || num > 4 ? option() : num);
}

// print provided book
void print(book b) {
	cout << b.title;
	// prettify the tab
	for (int i = 0, n = 3 - strlen(b.title)/8; i < n; i++) cout << "\t";
	cout << b.author << endl;
}
// print all books
void print_all() {
	clear();
	cout << "Title" << "\t\t\t" << "Author" << endl;
	cout << "-------" << endl;
	for (int i = 0; i < size; i++)	print(books[i]);
	pause();
}

// find book's id, return -1 if not found
int findBookId(char title[]) {
	for (int i = 0; i < size; i++)
		if (strcmp(tolower(books[i].title), tolower(title)) == 0)
			return i;
	pause();
	return -1;
}

// search by title
void searchByTitle() {
	clear();
	// ask what title to search
	char input[50];
	cout << "Book's Title: "; cin.ignore(); gets(input);
	cout << endl;
	// find book's id
	int id = findBookId(input);
	if (id < 0)	cout << "NOT FOUND\n";
	else		print(books[id]);
	pause();
}
// search by author
void searchByAuthor() {
	clear();
	// ask what author to search
	char input[50];
	cout << "Book's Author: "; cin.ignore(); gets(input);
	cout << endl;
	// loop all books
	bool found = false;
	for (int i = 0; i < size; i++) {
		// if found, print out
		if (strcmp(tolower(books[i].author), tolower(input)) == 0) {
			print(books[i]);
			found = true;
		}
	}
	if (!found)	cout << "NOT FOUND\n";
	pause();
}
// search option
void search() {
	clear();
	cout << "1 - Search by Title\n";
	cout << "2 - Search by Author\n";
	cout << "0 - Go Back\n\n";
	int num;
	cout << "Choose: "; cin >> num;
	switch (num) {
		default: search(); break;
		case 0: break;
		case 1: searchByTitle(); break;
		case 2: searchByAuthor(); break;
	}
}

// edit book's title
void editTitle() {
	clear();
	// ask for book to edit
	char input[50];
	cout << "Which Book? title: "; cin.ignore(); gets(input);
	// search book's
	int id = findBookId(input);
	// if not found
	if (id < 0) {
		editTitle();
		return;
	}
	// if book exits
	// display old record
	cout << "\nOld Record:\n";
	print(books[id]);
	// ask for new title
	char input2[50];
	cout << "\nNew Title: "; gets(input2);
	strcpy(books[id].title, input2);
	// display new record
	cout << "\nYEAH, New Record:\n";
	print(books[id]);
	pause();
}
// edit book's author
void editAuthor() {
	clear();
	// ask for book's title to edit
	char input[50];
	cout << "Which Book? title: "; cin.ignore(); gets(input);
	// find book's id
	int id = findBookId(input);
	// if not exist
	if (id < 0) {
		editAuthor();
		return;
	}
	// if exist
	// display old record
	cout << "\nOld Record:\n";
	print(books[id]);
	// ask for new author
	char input2[50];
	cout << "\nNew Author: "; gets(input2);
	strcpy(books[id].author, input2);
	// display new record
	cout << "\nYEAH, New Record:\n";
	print(books[id]);
	pause();
}
// edit option
void edit() {
	clear();
	cout << "1 - Edit Title\n";
	cout << "2 - Edit Author\n";
	cout << "0 - Go Back\n\n";
	int num;
	cout << "Choose: "; cin >> num;
	switch (num) {
		default: edit(); break;
		case 0: break;
		case 1: editTitle(); break;
		case 2: editAuthor(); break;
	}
}

// sort by title, using bubble sort algo
void sortByTitle() {
	int done, i, j;
	for (i = size-1; i > 0; i--) {
		done = true;
		for (j = 0; j < i; j++) {
			if (strcmp(books[j].title, books[j+1].title) > 0) {
				swap(books[j], books[j+1]);
				done = false;
			}
		}
		if (done) break;
	}
}
// sort by author, using bubble sort algo
void sortByAuthor() {
	int done, i, j;
	for (i = size-1; i > 0; i--) {
		done = true;
		for (j = 0; j < i; j++) {
			if (strcmp(books[j].author, books[j+1].author) > 0) {
				swap(books[j], books[j+1]);
				done = false;
			}
		}
		if (done) break;
	}
}
// sort option
void sort() {
	clear();
	cout << "1 - Sort by Title\n";
	cout << "2 - Sort by Author\n";
	cout << "0 - Go Back\n\n";
	int num;
	cout << "Choose: "; cin >> num;
	switch (num) {
		default: sort(); return;
		case 0: return;
		case 1: sortByTitle(); break;
		case 2: sortByAuthor(); break;
	}
	// display records after sort
	print_all();
}

main() {
	while (1) {
		int num = option();
		if (num == 0)	break;
		void (*operation[])() = {print_all, search, edit, sort};
		(*operation[num-1])();
	}
	cout << "\nThank you for using our Service.";
}
