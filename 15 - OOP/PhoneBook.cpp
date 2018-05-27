#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class PhoneBookItem {
	char	*name = NULL,
			*tel = NULL;
public:
	PhoneBookItem	*next = NULL,
					*prev = NULL;
	PhoneBookItem() {
		SetName(NULL);
		SetTel(NULL);
	}
	PhoneBookItem(const char* name, const char* tel) {
		SetName(name);
		SetTel(tel);
	}
	void SetName(const char *name) {
		if (this->name) delete []name;
		if (name) {
			this->name = new char[strlen(name) + 1];
			strcpy(this->name, name);
		} else
			this->name = NULL;
	}
	void SetTel(const char *tel) {
		if (this->tel) delete []tel;
		if (tel) {
			this->tel = new char[strlen(tel) + 1];
			strcpy(this->tel, tel);
		} else
			this->tel = NULL;
	}
	~PhoneBookItem() {
		SetName(NULL);
		SetTel(NULL);
		if (prev)	prev->next = next;
		if (next)	next->prev = prev;
	}
	inline char* GetName() {
		return name;
	}
	inline char* GetTel() {
		return tel;
	}
	inline void Cout() {
		cout << name << " --- " << tel << endl;
	}
};

class PhoneBook {
	PhoneBookItem	*head = NULL,
					*tail = NULL;
public:
	~PhoneBook() {
		Reset();
	}
	void Reset() {
		PhoneBookItem *temp;
		while (tail) {
			temp = tail->prev;
			delete tail;
			tail = temp;
		}
		head = NULL;
	}
	void Add(PhoneBookItem* item) {
		if (!head)	head = item;
		else {
			tail->next = item;
			item->prev = tail;
		}
		tail = item;
	}
	// search by name, return PhoneBookItem* or NULL
	PhoneBookItem* SearchByName(const char *name) {
		PhoneBookItem	*cur = head,
						*prev = NULL;
		while (cur) {
			if (strcmp(name, cur->GetName()) == 0)
				return cur;
			cur = cur->next;
		}
		return NULL;
	}
	// return true if name exists
	bool RemoveByName(const char *name) {
		PhoneBookItem *s = SearchByName(name);
		if (s) {
			if (s == head) head = tail = NULL;
			else if (s == tail) tail = s->prev;
			delete s;
			return true;
		}
		return false;
	}
	void CoutAll() {
		PhoneBookItem *cur = head;
		cout << "---***---" << endl;
		while (cur) {
			cur->Cout();
			cur = cur->next;
		}
	}
	void SaveToFile(const char *filename) {
		ofstream file(filename);
		PhoneBookItem *cur = head;
		while (cur) {
			file << cur->GetName() << " " << cur->GetTel() << endl;
			cur = cur->next;
		}
		file.close();
	}
	void OpenFromFile(const char *filename) {
		Reset();
		ifstream file(filename);
		PhoneBookItem *p = NULL;
		char input[100];
		while (file >> input) {
			if (!p) {
				p = new PhoneBookItem;
				p->SetName(input);
			} else {
				p->SetTel(input);
				this->Add(p);
				p = NULL;
			}
		}
		file.close();
	}
};

int main() {
	PhoneBook book;
	book.Add(new PhoneBookItem("Ouspheaktra", "010547560"));
	book.CoutAll();
	book.RemoveByName("Ouspheaktra");
	book.CoutAll();
	book.Add(new PhoneBookItem("Ouspheaktra", "010547560"));
	book.Add(new PhoneBookItem("Kimly", "35454"));
	book.CoutAll();
	book.RemoveByName("Kimly");
	book.CoutAll();
	book.Add(new PhoneBookItem("Kimly", "35454"));
	book.SaveToFile("test.txt");
	book.CoutAll();
	cout << "+++++++++++" << endl;
	book.OpenFromFile("test.txt");
	book.CoutAll();
}
