#include <iostream>
#include <string.h>
using namespace std;

class PhoneBookItem {
	char *name = NULL, *tel = NULL;
public:
	PhoneBookItem * next = NULL;
	PhoneBookItem(const char* _name, const char* _tel) {
		if (name)	delete []name;
		if (tel)	delete []tel;
		if (_name) {
			name = new char[strlen(_name) + 1];
			strcpy(name, _name);
		} else
			name = NULL;
		if (_tel) {
			tel = new char[strlen(_tel) + 1];
			strcpy(tel, _tel);	
		} else
			tel = NULL;
	}
	~PhoneBookItem() {
		this(NULL, NULL);
	}
	char* GetName() {
		return name;
	}
	char* GetTel() {
		return tel;
	}
};

class PhoneBook {
	PhoneBookItem	*head = NULL,
					*tail = NULL;
public:
	~PhoneBook() {
		PhoneBookItem *next;
		while (head) {
			next = head->next;
			delete head;
			head = next;
			
		}
	}
	void Add(PhoneBookItem* item) {
		if (!head)	head = item;
		else		tail->next = item;
		tail = item;
	}
	// return true if name exists
	bool RemoveByName(char *name) {
		PhoneBookItem	*cur = head,
						*prev = NULL;
		while (cur) {
			if (strcmp(name, cur->GetName()) == 0) {
				// if head
				if (cur == head)	head = cur->next;
				else				prev->next = cur->next;
				// if tail
				if (!cur->next)		tail = prev;
				delete cur;
				return true;
			}
			prev = cur;
			cur = cur->next;
		}
		return false;
	}
	void CoutAll() {
		PhoneBookItem *cur = head;
		cout << "---***---" << endl;
		while (cur) {
			cout << cur->GetName() << " --- " << cur->GetTel() << endl;
			cur = cur->next;
		}
	}
};

int main() {
	PhoneBook book;
	book.Add(new PhoneBookItem("Ouspheaktra", "010547560"));
	book.CoutAll();
	cout << "end";
	//book.RemoveByName("Ouspheaktra");
	//book.CoutAll();
	//book.Add(new PhoneBookItem("Kimly", "35454"));
	//book.Add(new PhoneBookItem("Ouspheaktra", "010547560"));
	//book.CoutAll();
}
