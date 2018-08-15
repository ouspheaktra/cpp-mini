#ifndef DICT_H
#define DICT_H

#include "list.h"

template <class KEY, class VALUE>
class Dict {
	List <KEY> k;
	List <VALUE> v;
public:
	void Clear() {
		k.Clear();
		v.Clear();
	}
	
	void Set(const KEY &key, const VALUE &value) {
		if (hasKey(key))
			(*this)[key] = value;
		else {
			k.Push(key);
			v.Push(value);
		}
	}
	
	bool hasKey(const KEY &key) {
		return k.Count(key);
	}
	
	List <KEY> keys() {
		return k;
	}
	List <KEY> values() {
		return v;
	}
	
	VALUE & operator[] (const KEY &key) {
		int id;
		try {
			id = k.IndexOf(key);
		} catch (int err) {
			throw 1;
		}
		return v[id];
	}
};

#endif
