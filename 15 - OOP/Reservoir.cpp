#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class Reservoir {
	char * name = NULL;
	float width, height, depth;
public:
	Reservoir() {
		SetName(NULL);
		SetDimension(0, 0, 0);
	}
	Reservoir(const char * name, float width, float height, float depth) {
		SetName(name);
		SetDimension(width, height, depth);
	}
	Reservoir(const Reservoir &r) {
		*this = r;
	}
	~Reservoir() {
		if (name)
			delete [] name;
	}
	
	void operator= (const Reservoir &r) {
		SetName(r.name);
		SetDimension(r.width, r.height, r.depth);
	}
	operator char* () {
		char *out = new char[100];
		char tmp[25] = {'\0'};
		strcpy(out, name);
		strcat(out, " ");
		snprintf(tmp, sizeof(tmp), "%.2f", width);
		strcat(out, tmp);
		strcat(out, " ");
		snprintf(tmp, sizeof(tmp), "%.2f", height);
		strcat(out, tmp);
		strcat(out, " ");
		snprintf(tmp, sizeof(tmp), "%.2f", depth);
		strcat(out, tmp);
	}
	
	char *GetName() {
		return name;
	}
	void SetName(const char * name) {
		if (this->name)
			delete [] this->name;
		if (name) {
			this->name = new char[strlen(name) + 1];
			strcpy(this->name,  name);
		} else
			this->name = NULL;
	}
	void SetDimension(float width, float height, float depth) {
		this->width = width;
		this->height = height;
		this->depth = depth;
	}
	float GetVolumn() const {
		return width*height*depth;
	}
	float GetSurface() const {
		return width*height*2 + width*depth*2 + height*depth*2;
	}
	int Compare(const Reservoir &r) {
		if (this->GetVolumn() > r.GetVolumn())
			return 1;
		else if (this->GetVolumn() < r.GetVolumn())
			return -1;
		return 0;
	}
};

class ReservoirList {
	Reservoir **value;
	int size;
public:
	ReservoirList() {
		value = NULL;
		size = 0;
	}
	~ReservoirList() {
		Reset();
	}
	
	void Reset() {
		if (value) {
			for (int i = 0; i < size; i++)
				delete value[i];
			//delete [] value;
		}
		size = 0;
	}
	void AddReservoir(const Reservoir &reservoir) {
		AddReservoir(new Reservoir(reservoir));
	}
	void AddReservoir(Reservoir &reservoir) {
		AddReservoir(&reservoir);
	}
	void AddReservoir(Reservoir *reservoir) {
		Reservoir **tmp = value;
		value = new Reservoir*[size + 1];
		for (int i = 0; i < size; i++)
			value[i] = tmp[i];
		value[size++] = reservoir;
		if (tmp)
			delete [] tmp;
	}
	void RemoveByName(const char * name) {
		Reservoir **tmp = new Reservoir*[size];
		int nSize = 0;
		for (int i = 0; i < size; i++)
			if (strcmp(name, value[i]->GetName()) != 0)
				tmp[nSize++] = value[i];
			else
				delete value[i];
		delete [] value;
		value = new Reservoir*[nSize];
		for (int i = 0; i < nSize; i++)
			value[i] = tmp[i];
		size = nSize;
	}
	void Cout() {
		cout << "\nreservoirs:" << endl;
		for (int i = 0; i < size; i++)
			cout << *value[i] << endl;
	}
	void SaveToFile(const char *filename) {
		ofstream file(filename);
		for (int i = 0; i < size; i++)
			file << *value[i] << endl;
		file.close();
	}
	void ReadFromFile(const char *filename) {
		Reset();
		ifstream file(filename);
		char input[4][100];
		char time = 0;
		while (file >> input[time])
			if (++time == 4) {
				AddReservoir( Reservoir(input[0], atof(input[1]), atof(input[2]), atof(input[3])) );
				time = 0;
			}
		file.close();
	}
	
	Reservoir &operator[] (int i) {
		return *value[i];
	}
};

int main() {
	ReservoirList r;
	r.AddReservoir( Reservoir("room", 5, 6, 4) );
	r.AddReservoir( Reservoir("car", 0.5, 2.3, 0.6) );
	r.Cout();
	r.RemoveByName("room");
	r.Cout();
	r.AddReservoir( Reservoir("table", 1.3, 0.5, 1) );
	r.AddReservoir( Reservoir("bicyble", 0.3, 1.5, 1) );
	r.Cout();
	r.SaveToFile("test.txt");
	r.Reset();
	r.Cout();
	r.ReadFromFile("test.txt");
	r.Cout();
}
