/*
	KNIGHT OF CHESS GAME
	---
	show all possible move by providing a starting point
*/

#include <iostream>
using namespace std;

const short size = 4;			// size of chess board
int board[size][size] = {0};	// starting move

void moveKnight(int move);		// move the knight according to the provided move
void coutBoard();

main() {
	int start;
	
	// input starting point
	while(true) {
		cout << "Input a number where ur KNIGHT should be placed : "; cin >> start;
		if (start < 0 || start >= size*size)
			cout << start << " is out of the chess\n\n";
		else break;
	}
	
	// put starting point into the board
	board[start/size][start%size] = 1;
	
	// move the knight from 1, it will be put 2 into the board
	moveKnight(1);
	
	coutBoard();
}

void moveKnight(int move) {
	// all possible move of the knight
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
	
	// represent there is no possible move
	int noPossibleMove = true;
	for (int r = 0; r < size; r++) {		// row of board
		for (int c = 0; c < size; c++) {	// col of board
		
			// if the current tile is the number of provided move, than move the knight
			if (board[r][c] == move) {
			
				// move the knight to all possible tile		
				for (int p = 0; p < 8; p++) {
					int my = r + possibleMove[p][0];
					int mx = c + possibleMove[p][1];
					if (my >= 0 && my < size && mx >= 0 && mx < size) {
						// move the knight to this tile (board[my][mx])
						if (board[my][mx] == 0) {
							board[my][mx] = move+1;
							
							// the knight has been move, so 'there is no possible move' is not true anymore
							noPossibleMove = false;
						}
					}
				}
			}
		}
	}
	
	// if there are possible move, move to the next
	if (!noPossibleMove)
		moveKnight(move+1);
}

void coutBoard() {
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
