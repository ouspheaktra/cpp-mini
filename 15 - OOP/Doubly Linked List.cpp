#include <iostream>
using namespace std;

template <class TYPE>
class Array;

template <class T>
class Node {
	T * value;
	Node *next = NULL;
	Node *prev = NULL;
	
	template <class TYPE>
	friend class Array;
	
	void SetPrev(Node <T> *node) {
		if (prev)
			prev->SetNext(node);
		else {
			prev = node;
			node->next = this;
		}
	}
	void SetNext(Node <T> *node) {
		if (node) {
			node->prev = this;
			node->next = this->next;
			if (this->next != NULL)
				this->next->prev = node;
		}
		this->next = node;
	}
public:
	Node(T * value) : value(value) { }
	void SetValue(int value) {
		this->value = value;
	}
	void Cout() {
		cout << *value << endl;
	}
};



template <class TYPE>
class Array {
	Node <TYPE> *head, *tail;
	int length;
	Node <TYPE> * GetNodeAt(unsigned int index) {
		if (index >= length)
			index = length - 1;
		Node <TYPE> *node = head;
		for (int i = 0; i < index; i++)
			node = node->next;
		return node;
	}
public:
	Array() : head(NULL), tail(NULL), length(0) { }
	
	int GetLength() {
		return length;
	}
	bool isEmpty() {
		return (length == 0);
	}
	TYPE & GetAt(unsigned int index) {
		return *(GetNodeAt(index)->value);
	}
	
	void Append(const TYPE &value) {
		Append(new Node <TYPE> ( new TYPE(value) ));
	}
	void Append(TYPE &value) {
		Append(new Node <TYPE> (&value));
	}
	void Append(TYPE *value) {
		Append( new Node <TYPE> (value) );
	}
	void Append(Node <TYPE> * node) {
		if (head == NULL)
			head = tail = node;
		else {
			tail->SetNext(node);
			tail = node;
		}
		length++;
	}
	
	void Insert(unsigned int index, const TYPE &value) {
		Insert(index, new Node <TYPE> (new TYPE(value)));
	}
	void Insert(unsigned int index, TYPE &value) {
		Insert(index, new Node <TYPE> (&value));
	}
	void Insert(unsigned int index, TYPE * value) {
		Insert(new Node <TYPE> (value));
	}
	void Insert(unsigned int index, Node <TYPE> * node) {
		if (length == 0 || index >= length)
			return Append(node);
		Node <TYPE> * nodeAtId = GetNodeAt(index);
		nodeAtId->SetPrev(node);
		if (nodeAtId == head)
			head = node;
		length++;
	}
	
	void Pop() {
		if (head == NULL)
			return;
		if (head == tail) {
			head = tail = NULL;
		} else {
			tail = tail->prev;
			tail->SetNext(NULL);
		}
		length--;
	}
	void Remove(unsigned int index) {
		if (length == 1 || index >= length - 1)
			return Pop();
		Node <TYPE> * nodeAtId = GetNodeAt(index);
		Node <TYPE> * prevNode = nodeAtId->prev;
		Node <TYPE> * nextNode = nodeAtId->next;
		if (nodeAtId == head) {
			nextNode->prev = NULL;
			head = nextNode;
		} else {
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
		}
		length--;
	}
	void Empty() {
		while (head)
			Pop();
	}
	
	void Cout() {
		Node <TYPE> * cur = head;
		while (cur) {
			cur->Cout();
			cur = cur->next;
		}
	}
	
	TYPE & operator [] (unsigned int i) {
		return GetAt(i);
	}
};

int main() {
	Array <int> array;
	array.Append(12);
	array.Append(30);
	array.Append(40);
	array.Insert(1, 800);
	array.Remove(1);
	array[2] = 10000;
	array.Cout();
}
