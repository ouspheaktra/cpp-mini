#include <iostream>
using namespace std;

class Item {
	int value;
	Item *next = NULL;
public:
	Item(int value) : value(value) { }
	void Cout() {
		cout << value << endl;
	}
	void SetNext(Item *next) {
		this->next = next;
	}
	Item * GetNext() {
		return this->next;
	}
};

class List {
	Item *head, *tail;
public:
	List() : head(NULL), tail(NULL) { }
	
	void Push(const Item &item) {
		Push(new Item(item));
	}
	void Push(Item &item) {
		Push(&item);
	}
	void Push(Item *item) {
		if (head == NULL)
			head = tail = item;
		else {
			tail->SetNext(item);
			tail = item;
		}
	}
	
	Item * Pop() {
		Item * oldTail = tail;
		if (head == tail)
			head = tail = NULL;
		else {
			Item * preTail = head;
			while (preTail && preTail->GetNext() != tail)
				preTail = preTail->GetNext();
			tail = preTail;
			tail->SetNext(NULL);
		}
		return oldTail;
	}
	
	void Cout() {
		Item * cur = head;
		while (cur) {
			cur->Cout();
			cur = cur->GetNext();
		}
	}
};

int main() {
	List list;
	list.Push(Item(12));
	list.Push(Item(20));
	list.Pop();
	list.Cout();
}
