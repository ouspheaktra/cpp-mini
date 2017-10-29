#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
using namespace std;

const short size = 3;
int board[size][size];
int user = -1;
int pc = -2;
int turn = user;

void init();	// initialize the board
void draw();	// draw the board out
int pcMove();	// pc generate which tile to move
bool move(int tile);	// move the tile
int winner();	// who win this round

main() {
	
	// greeting
	cout << "WELCOME TO TIC-TAC-TOE\n";
	Sleep(1500);
	srand(time(NULL));
	int tile;
	int win;
	
	init();
	
	// play until win
	do {
		system("cls");
		
		if (turn == user)	cout << "YOUR TURN\n\n";
		else				cout << "COMPUTER'S TURN\n\n";
		
		draw();
		
		// move
		if (turn == user) {
			// ask the user to move
			cout << "\nTile to choose: "; cin >> tile;
		} else {
			// computer generate move
			tile = pcMove();
		}
        
        // move if possible, else report illegality
        if (move(tile)) {
            if (turn == user)	turn = pc;
        	else				turn = user;
        } else {
        	cout << "\nIllegal move.\n";
            Sleep(750);
		}
		win = winner();
	} while (!win);	// while no winner, keep playing
	
	// THE WINNER IS ...
	system("cls");
	draw();
	if (win == -10)
		cout << "\nNO WINNER";
	else if (win == user)
		cout << "\nYOU ARE THE WINNER";
	else if (win == pc)
		cout << "\nCOMPUTER IS THE WINNER";
}

void init() {
    int num = 0;
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            board[row][col] = num++;
}

void draw() {
	for (int col = 0; col < size; col++) cout << " _____";
	cout << endl;
	
    for (int row = 0; row < size; row++) {
    	
    	for (int col = 0; col < size; col++) cout << "|     ";
    	cout << "|" << endl;
    	
        for (int col = 0; col < size; col++) {
        	cout << "|  ";
        	if (board[row][col] == user)	cout << "X";
        	else if (board[row][col] == pc)	cout << "#";
        	else							cout << board[row][col];
			cout << "  ";
		}
		cout << "|" << endl;
		
        for (int col = 0; col < size; col++) cout << "|_____";
    	cout << "|" << endl;
    }
}

// find one needed to win
// return that one as the number represent that tile
// return -1 means need more than one
int needOneToWin(int tile) {
	int r = tile/size;
	int c = tile%size;
	if (r == 2 && c == 2) {
		int a = 5;
		a = 7;
	}
	for (int y = 1; y >= -1; y--) {		// move to y
		for (int x = 1; x >= -1; x--) {	// move to x
			if (y == 0 && x == 0)	continue;	// (0,0) means not move. so over it
			int needOne = 0;
			int needOneTile = 0;
			for (int t = 1; t < size; t++) {	// number of strike
				int my = r + y*t;
				int mx = c + x*t;
				if (my >= 0 && my < size && mx >= 0 && mx < size) {	// if it's inside the board
					if (board[my][mx] != board[r][c]) {
						needOne++;
						if (needOne == 1)
							needOneTile = my*size + mx;
					}
				} else {
					needOne = 0;
					break;
				}
			}
			if (needOne == 1 && board[needOneTile/size][needOneTile%size] != pc) 
				return needOneTile;
		}
	}
	return -1;
}

int pcMoveRandomly() {
	int number = rand()%(size*size);
	if (board[number/size][number%size] > 0)
		return number;
	else
		return pcMoveRandomly();
}
int pcBlockUser() {
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			if (board[r][c] == user) {
				int needOne = needOneToWin(r*size + c);
				if (needOne != -1) return needOne;
			}
		}
	}
	return -1;
}
int pcMove() {
	// if middle not yet set, set in the middle
	if (board[size/2][size/2] >= 0) return (int)(size/2)*size+(int)(size/2);
	
	// try to block the user
	int blockUser = pcBlockUser();
	if (blockUser != -1) return blockUser;
	
	return pcMoveRandomly();
}

bool move(int tile) {
    if (tile < 0 || tile >= size*size || board[tile/size][tile%size] < 0)
    	return false;
	board[tile/size][tile%size] = turn;
	return true;
}

// board in provided r and c
// is it in-a-row
// return 0 if no in-a-row
// return not 0 indicate the user or the pc
int isInRow(int tile) {
	int r = tile/size;
	int c = tile%size;
	for (int y = 1; y >= -1; y--) {		// move to y
		for (int x = 1; x >= -1; x--) {	// move to x
			if (y == 0 && x == 0)	continue;	// (0,0) means not move. so over it
			bool inRow = true;
			for (int t = 1; t < size; t++) {	// number of strike
				int my = r + y*t;
				int mx = c + x*t;
				if (my >= 0 && my < size && mx >= 0 && mx < size) {	// if it's inside the board
					if (board[r][c] != board[my][mx]) {
						inRow = false;
						break;
					}
				} else {
					inRow = false;
					break;
				}
			}
			if (inRow)	return board[r][c];
		}
	}
	return 0;
}

bool noMoreMove() {
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			if (board[r][c] >= 0)
				return false;
	return true;
}

// return 0 means no winner yet
// return < 0 indicate user or pc is a winner
// return -10 means no move available
int winner() {
	if (noMoreMove())
		return -10;
		
	for (int row = 0; row < size; row++) {		// row
		for (int col = 0; col < size; col++) {	// col
			if (board[row][col] < 0) {
				int result = isInRow(row*size + col);		// is the current row and col is in-a-row
				if (result) return result;
			}
		}
	}
    return 0;
}
