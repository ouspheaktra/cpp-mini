#include <iostream>
using namespace std;

template <class TYPE> class Array;

class Node {
	int value;
	Node *next = NULL;
	Node *prev = NULL;
	
	template <class TYPE>
	friend class Array;
	
	void SetPrev(Node *node) {
		if (prev)
			prev->SetNext(node);
		else {
			prev = node;
			node->next = this;
		}
	}
	void SetNext(Node *node) {
		if (node) {
			node->prev = this;
			node->next = this->next;
			if (this->next != NULL)
				this->next->prev = node;
		}
		this->next = node;
	}
public:
	Node(int value) : value(value) { }
	void SetValue(int value) {
		this->value = value;
	}
	void Cout() {
		cout << value << endl;
	}
};

template <class TYPE>
class Array {
	TYPE *head, *tail;
	int length;
public:
	Array() : head(NULL), tail(NULL), length(0) { }
	
	int GetLength() {
		return length;
	}
	bool isEmpty() {
		return (length == 0);
	}
	TYPE & GetAt(unsigned int index) {
		if (index >= length)
			index = length - 1;
		TYPE *node = head;
		for (int i = 0; i < index; i++)
			node = node->next;
		return *node;
	}
	
	void Append(const TYPE &node) {
		Append(new TYPE(node));
	}
	void Append(TYPE &node) {
		Append(&node);
	}
	void Append(TYPE *node) {
		if (head == NULL)
			head = tail = node;
		else {
			tail->SetNext(node);
			tail = node;
		}
		length++;
	}
	
	void Insert(unsigned int index, const TYPE &node) {
		Insert(index, new TYPE(node));
	}
	void Insert(unsigned int index, TYPE &node) {
		Insert(index, &node);
	}
	void Insert(unsigned int index, TYPE *node) {
		if (length == 0 || index >= length)
			return Append(node);
		TYPE * nodeAtId = &GetAt(index);
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
		TYPE * nodeAtId = &GetAt(index);
		TYPE * prevNode = nodeAtId->prev;
		TYPE * nextNode = nodeAtId->next;
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
		TYPE * cur = head;
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
	Array <Node> array;
	array.Append(Node(12));
	array.Append(Node(200));
	array.Append(Node(321));
	array.Pop();
	array.Insert(1, Node(50));
	array.Append(Node(1000));
	array.Insert(0, Node(10000));
	array.Cout();
	cout << "---" << endl;
	array.Remove(0);
	array.Cout();
	array[13].SetValue(999);
	cout << "---" << endl;
	array.Cout();
}
