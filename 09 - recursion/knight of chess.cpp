/*
	KNIGHT OF CHESS GAME
	---
	show all possible move by providing a starting point
*/

#include <iostream>
using namespace std;

const short size = 4;			// size of chess board
int board[size][size] = {0};	
int move = 1;					// starting move
int limit;						// limit the number of boards
int numberOfBoard = 0;			// number of boards

void moveKnight(int num);
void coutBoard();

main() {
	int start;
	
	while(true) {
		cout << "Input a number where ur KNIGHT should be placed : "; cin >> start;
		if (start < 0 || start >= size*size)
			cout << start << " is out of the chess\n\n";
		else break;
	}
	
	while(true) {
		cout << "\nInput how many of boards you want to display (0 means all) : "; cin >> limit;
		if (limit < 0)
			cout << "Limit cannot be less than 0\n";
		else break;
	}
	
	moveKnight(start);
}

void moveKnight(int num) {
	board[num/size][num%size] = move++;
	int possibleMove[8][2] = {
		{-2, -1},
		{-2, 1},
		{-1, -2},
		{-1, 2},
		{1, -2},
		{1, 2},
		{2, -1},
		{2, 1},
	};
	bool noPossibleMove = true;
	for (int p = 0; p < 8; p++) {
		int my = num/size + possibleMove[p][0];
		int mx = num%size + possibleMove[p][1];
		if (my >= 0 && my < size && mx >= 0 && mx < size) {
			if (board[my][mx] == 0) {
				moveKnight(my*size + mx);
				board[my][mx] = 0;
				move--;
				noPossibleMove = false;
				// return; // uncomment this to see only one
			}
		}
	}
	if (noPossibleMove) {
		coutBoard();
	}
}

void coutBoard() {
	if (limit != 0 && numberOfBoard == limit) return;
	cout << endl << "---   " << ++numberOfBoard << endl;
	for (int c = 0; c < size; c++) cout << "-----";
	cout << endl;
	for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
        	cout << "| " <<board[r][c];
        	if (board[r][c] < 10)	cout << "  ";
        	else					cout << " ";
        }
        cout << endl;
        for (int c = 0; c < size; c++) cout << "|----";
        cout << endl;
    }
}
