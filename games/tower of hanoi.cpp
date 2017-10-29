/*
	TOWER OF HANOI
*/
#include <iostream>
#include <windows.h>
#include <utility>
using namespace std;

short maxDisk;
const short poleNum = 3;
short disk[poleNum][100];
short from, to;
int moveNum = 0;

void init();
void draw();
void moveFrom();
void moveTo();
bool win();

main() {
	init();		// initialize the game
	draw();		// draw the first image
	do {
		moveFrom();
		moveTo();
	} while (!win());	// play while not win
	cout << "YOU WIN\n";
	cout << "you move " << moveNum << " times.";
}

// initialize the game, put all disks in pole a (smallest on top)
void init() {
	cout << "WELCOME TO THE TOWER OF HANOI\n\n";
	
	// ask the user, how many disks
	while (1) {
		cout << "Input number of DISK : "; cin >> maxDisk;
		if (maxDisk < 2 || maxDisk > 9)
			cout << "!!! number of DISK should be from 2 to 9 !!!\n\n";
		else
			break;
	}
	maxDisk++;
	Sleep(500);
	
	for (int i = 0; i < maxDisk; i++)
		disk[0][i] = i;
}

// draw the image
void draw() {
	system("cls");
	cout << "\n\n";
	for (int d = 0; d < maxDisk; d++) {
		for (int p = 0; p < poleNum; p++) {
			cout << "  ";
			short radius = disk[p][d];
			for (int s = 0; s < maxDisk-radius; s++)	cout << " ";
			if (radius == 0)	cout << " || ";
			else {
				cout << "(";
				for (int s = 1; s <= radius; s++)	cout << "X";
				cout << "XX"; 
				for (int s = 1; s <= radius; s++)	cout << "X";
				cout << ")";
			}
			for (int s = 0; s < maxDisk-radius; s++)	cout << " ";
		}
		cout << endl;
	}
	cout << "  ";
	for (int s = 0; s <= maxDisk; s++)	cout << " ";
	cout << "0 ";
	for (int s = 0; s <= maxDisk; s++)	cout << " ";
	cout << "  ";
	for (int s = 0; s <= maxDisk; s++)	cout << " ";
	cout << "1 ";
	for (int s = 0; s <= maxDisk; s++)	cout << " ";
	cout << "  ";
	for (int s = 0; s <= maxDisk; s++)	cout << " ";
	cout << "2\n\n";
}

// check if provided pole is zero
bool isZero(int pole) {
	for (int d = 0; d < maxDisk; d++)
		if (disk[pole][d] != 0)
			return false;
	return true;
}

// ask the user to input which pole to move from
void moveFrom() {
	while (1) {
		cout << "move FROM "; cin >> from;
		if (from < 0 || from >= poleNum)
			cout << "!!! 0 to " << poleNum-1 << " !!! please\n";
		else
			if (isZero(from))	cout << "in pole " << from << ", no disk to move\n\n";
			else				break;
	}
	
	// up the disk by moving the top one to the last index
	for (int d = 0; d < maxDisk; d++) {
		if (disk[from][d] != 0) {
			swap(disk[from][d], disk[from][0]);
			break;
		}
	}
	
	// draw again
	draw();
}

bool movable() {
	// if put to the same pole
	if (from == to) {
		for (int d = 1; d < maxDisk; d++) {
			if (d == maxDisk-1 || disk[to][d+1] != 0) {
				disk[to][d] = disk[from][0];
				disk[from][0] = 0;
				return true;
			}
		}
	}
	
	// if put to the empty pole
	if (isZero(to)) {
		disk[to][maxDisk-1] = disk[from][0];
		disk[from][0] = 0;
		moveNum++;
		return true;
	}
	
	// if simple
	for (int d = 0; d < maxDisk; d++) {
		if (disk[to][d] != 0) {
			if (disk[from][0] <= disk[to][d]) {
				disk[to][d-1] = disk[from][0];
				disk[from][0] = 0;
				moveNum++;
				return true;
			} else 
				return false;
		}
	}
}

// ask the user to input which pole to move to
void moveTo() {
	while (1) {
		cout << "move TO   "; cin >> to;
		if (to < 0 || to >= poleNum)
			cout << "!!! 0 to " << poleNum-1 << " !!! please\n";
		else
			if (!movable()) cout << "You cannot put a disk on a smaller disk.\n\n";
			else			break;
	}
	draw();
}

// check if win the game
bool win() {
	for (int d = 0; d < maxDisk; d++)
		if (disk[poleNum-1][d] != d)
			return false;
	return true;
}
