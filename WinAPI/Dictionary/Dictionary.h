#pragma once

#include <fstream>
#include "D:\cpp-mini\classes\string.h"

class DictItem {
	String word;
	String def;
public:
	DictItem() {}
	DictItem(String word, String def) : word(word), def(def) { }

	String GetWord() {
		return word;
	}
	String GetDef() {
		return def;
	}
};

class Dict {
	String filename;
	DictItem *item;
	int size;
public:
	Dict() : item(NULL), size(0) { }
	~Dict() {
		if (item)
			delete[] item;
	}

	void SetFile(String filename) {
		this->filename = filename;
		std::ifstream f(filename);
		char temp[256];
		bool isWord = false;
		if (f) {
			String word, def, line;
			while (!f.eof()) {
				f.getline(temp, 256);
				if (isWord) {
					if (word)
						AddItem(DictItem(word, def));
					word = temp;
					def = "";
				}
				else if (String(temp) != String("---"))
					def += String(temp) + String("\n");
				isWord = (String(temp) == String("---"));
			}
			if (word)
				AddItem(DictItem(word, def));
		}
		f.close();
	}

	DictItem * GetItem() {
		return item;
	}
	int GetItemSize() {
		return size;
	}

	DictItem *AddItem(const DictItem &dictItem) {
		DictItem *temp = new DictItem[size + 1];
		for (int i = 0; i < size; i++)
			temp[i] = item[i];
		temp[size] = dictItem;
		if (item)	delete[] item;
		item = temp;
		return &item[size++];
	}
	DictItem *Search(String word) {
		for (int i = 0; i < size; i++)
			if (item[i].GetWord() == word)
				return &item[i];
		return NULL;
	}
	void SaveItemToFile(DictItem *item) {
		std::ofstream f(filename, std::ofstream::app);
		if (f)
			f	<< "---" << std::endl
				<< item->GetWord().ToChar() << std::endl
				<< item->GetDef().ToChar() << std::endl;
		f.close();
	}
	DictItem * AddAndSave(const DictItem &dictItem) {
		DictItem *item = AddItem(dictItem);
		SaveItemToFile( item );
		return item;
	}
};