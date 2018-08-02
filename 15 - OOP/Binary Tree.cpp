#include <iostream>
using namespace std;

template <class TYPE>
class Tree {
	TYPE * value;
	Tree * parent;
	Tree * left;
	Tree * right;
public:
	Tree <TYPE> (const TYPE & value) : Tree <TYPE> (new TYPE (value)) { };
	Tree <TYPE> (TYPE & value) : Tree <TYPE> (&value) { };
	Tree <TYPE> (TYPE * value) : value(value), parent(NULL), left(NULL), right(NULL) {
		SetValue(value);
	}
	~Tree <TYPE> () {
		if (left)	delete left;
		if (right)	delete right;
		delete value;
	}
	
	void SetValue(const TYPE & value) {	SetValue(new TYPE (value)); }
	void SetValue(TYPE & value) {		SetValue(&value);	}
	void SetValue(TYPE * value) {
		this->value = value;
	}
	TYPE & GetValue() {
		return *value;
	}
	
	void Add(const TYPE & value) {	Add(new TYPE (value)); }
	void Add(TYPE & value) {		Add(&value); }
	void Add(TYPE * value) {
		if (*value <= *this->value) {
			if (this->left)
				this->left->Add(value);
			else {
				this->left = new Tree <TYPE> (value);
				this->left->parent = this;
			}
		} else {
			if (this->right)
				this->right->Add(value);
			else {
				this->right = new Tree <TYPE> (value);
				this->right->parent = this;
			}
		}
	}
	
	Tree <TYPE> * GetSearch(const TYPE & value) {
		TYPE val = value;
		return GetSearch(val);
	}
	Tree <TYPE> * GetSearch(TYPE & value) {
		if (value == *this->value)
			return this;
		if (value <= *this->value) {
			if (this->left)
				return this->left->GetSearch(value);
		} else
			if (this->right)
				return this->right->GetSearch(value);
		return NULL;
	}
	bool Search(const TYPE & value) {
		TYPE val = value;
		return Search(val);
	}
	bool Search(TYPE & value) {
		return (GetSearch(value) != NULL);
	}
	
	Tree <TYPE> * GetMin() {
		Tree * tree = this;
		while (true) {
			if (tree->left)
				tree = tree->left;
			else
				return tree;
		}
	}
	TYPE & Min() {
		return GetMin()->GetValue();
	}
	
	Tree <TYPE> * GetMax() {
		Tree * tree = this;
		while (true) {
			if (tree->right)
				tree = tree->right;
			else
				return tree;
		}
	}
	TYPE & Max() {
		return GetMax()->GetValue();
	}
	Tree <TYPE> * GetNext() {
		Tree <TYPE> * tree = this;
		if (tree->right != 0)
			return tree->right->GetMin();
		Tree <TYPE> * parent = this->parent;
		while (parent && tree == parent->right) {
			tree = parent;
			parent = parent->parent;
		}
		return parent;
	}
	Tree <TYPE> * GetPrevious() {
		Tree <TYPE> * tree = this;
		if (tree->left != 0)
			return tree->left->GetMax();
		Tree <TYPE> * parent = this->parent;
		while (parent && tree == parent->left) {
			tree = parent;
			parent = parent->parent;
		}
		return parent;
	}
	void Delete() {
		if (left && right) {
			Tree <TYPE> * rightParent = left->GetMax();
			rightParent->right = right;
			right->parent = rightParent;
			right = NULL;
		}
		
		if (parent) {
			if (right && !left) {
				parent->right = right;
				right->parent = parent;
			} else if (left && !right) {
				parent->left = left;
				left->parent = parent;
			} else if (!left && !right) {
				if (parent->right == this)
					parent->right = NULL;
				else
					parent->left = NULL;
			}
			right = NULL;
			left = NULL;
			delete this;
		// root
		} else {
			if (!left && !right) {
				delete this;
			} else {
				Tree <TYPE> * tmpRoot = (left ? left : right);
				value = tmpRoot->value;
				left = tmpRoot->left;
				right = tmpRoot->right;
				tmpRoot->value = NULL;
				tmpRoot->right = tmpRoot->left = NULL;
				delete newRoot;
			}
		}
	}
	void Cout() {
		if (left)	left->Cout();
		cout << *value << endl;
		if (right)	right->Cout();
	}
};

int main() {
	Tree <int> root(50);
	root.Add(23);
	root.Add(100);
	root.Add(12);
	root.Add(200);
	root.Add(45);
	root.Add(5000);
	root.GetSearch(45)->Delete();
	root.Cout();
	cout << "---" << endl;
	cout << root.Search(5000) << endl;
	cout << root.Min() << endl;
	cout << root.Max() << endl;
	cout << root.GetValue() << endl;
}
