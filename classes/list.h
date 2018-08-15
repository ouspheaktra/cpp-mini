#ifndef LIST_H
#define LIST_H

template <class TYPE>
class List {
	
	template <class T>
	class Node {
	public:
		T value;
		Node <T> *next = NULL;
		Node <T> *prev = NULL;
		Node(T value) : value(value) { }
	};
	
	Node <TYPE> *head = NULL;
	
	Node <TYPE> *Pre(Node <TYPE> *node) {
		if (!head)
			return NULL;
		Node <TYPE> *cur = head;
		while (cur) {
			if (cur->next == node)
				return cur;
			cur = cur->next;
		}
		return NULL;
	}
	Node <TYPE> *At(int id) {
		int length = Length();
		if (id < 0)
			id = length + id;
		if (id >= length)
			throw 1;
		Node <TYPE> *cur = head;
		int i = 0;
		while (i < id) {
			if (!cur->next)
				return cur;
			cur = cur->next;
			i++;
		}
		return cur;
	};
	
public:
	~List() {
		Clear();
	}
	
	int Length() {
		int length = 0;
		Node <TYPE> *tail = head;
		while (tail) {
			tail = tail->next;
			length++;
		}
		return length;
	}

	void Push(TYPE value) {
		Node <TYPE> *tail = At(-1);
		(tail ? tail->next : head) = new Node <TYPE>(value);
	}
	
	void Insert(unsigned int id, TYPE value) {
		if (id >= Length()) {
			Append(value);
			return;
		}
		Node <TYPE> *node;
		try {
			node = At(id);
		} catch (int i) {
			node = At(-1);
		}
		Node <TYPE> *newNode = new Node <TYPE> (value);
		newNode->next = node;
		(head == node ? head : Pre(node)->next) = newNode;
	}
	
	TYPE RemoveById(int id) {
		Node <TYPE> *node = (id < 0 ? At(-1) : At(id));
		(head == node ? head : Pre(node)->next) = node->next;
		TYPE out = node->value;
		delete node;
		return out;
	}
	
	TYPE Pop() {
		return RemoveById(-1);
	}
	
	void Clear() {
		while (head)
			Pop();
	}
	
	int IndexOf(TYPE value) {
		for (int i = 0, n = Length(); i < n; i++)
			if ((*this)[i] == value)
				return i;
		throw 1;
	}
	
	int Count(TYPE value) {
		int count = 0;
		for (int i = 0, n = Length(); i < n; i++)
			if ((*this)[i] == value)
				count++;
		return count;
	}
	
	List <TYPE> Copy() {
		List <TYPE> newList;
		for (int i = 0, n = Length(); i < n; i++)
			newList.Append((*this)[i]);
		return newList;
	}
	
	TYPE & operator [] (int id) {
		Node <TYPE> * at = At(id);
		return at->value;
	}
};

#endif