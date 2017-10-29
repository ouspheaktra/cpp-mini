#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <utility>
using namespace std;

const short maximum = 10;
const short minimum = 3;
int board[maximum][maximum];
const int direction = 4;
const int dimension = 2;
int possibleMove[direction][dimension] = {
	{0, 1},
	{0, -1},
	{1, 0},
	{-1, 0}
};
short hor;
short ver;

void init();	// initialize the board
void draw();	// draw the board out
bool move(int tile);	// move the tile
bool win();		// check if it is win

main() {
	
	// greeting
	cout << "WELCOME TO GAME OF FIFTEEN\n";
	
	while (1) {
		cout << "\nHow many Rows? "; cin >> ver;
		if (ver < minimum || ver > maximum)
			cout << "Number of Rows have to be from 3 to 10.\n";
		else
			break;
	}
	
	while (1) {
		cout << "\nHow many Columns? "; cin >> hor;
		if (hor < minimum || hor > maximum)
			cout << "Number of Rows have to be from 3 to 10.\n";
		else
			break;
	}
	
	init();

	// play until win
	while(true) {
		system("cls");
		draw();
		
		if (win()) break;
		
		// prompt for move
		int tile;
        cout << "\nTile to move: ";
        cin >> tile;
        
        // move if possible, else report
        if (!move(tile)) {
            cout << "\nIllegal move.";
            Sleep(750);
        }
	}
	
	cout << "\nYOU WIN";
}

void init() {
	srand(time(NULL));
	int num = 0;
    for (int row = 0; row < ver; row++)
        for (int col = 0; col < hor; col++)
        	board[row][col] = num++;
    
    short br = 0;
    short bc = 0;
    
    // swap randomly 1000 times
    for (int t = 0; t < 1000; t++) {
    	short randDir = rand()%direction;	// random direction
    	int my = br+possibleMove[randDir][0];	
    	int mx = bc+possibleMove[randDir][1];
    	if (my >= 0 && my < ver && mx >= 0 && mx < hor) {	// if not out of the board
    		swap(board[br][bc], board[my][mx]);	// swap blank and randomDirection
    		br = my;
    		bc = mx;
		} else {	// if out of the board. do it again
			t--;
			continue;
		}
	}
    	
    /*
    // one move to win (for TESTING ONLY)
    int value = 1;  //value to check
    for (int row = 0; row < ver; row++) {
        for (int col = 0; col < hor; col++) {
            board[row][col] = value;
            if (value == (ver * hor) - 1)
                board[row][col] = 0;
            if (value == hor * ver)
                board[row][col] = (ver * hor) - 1;
            value++;
        }
    }*/
}

void draw() {
    // print the board
    for (int row = 0; row < ver; row++) {
        for (int col = 0; col < hor; col++) {
            // replace 0 with underscore, and print
            if (board[row][col] == 0)
                cout << "_   ";
            else {
            	cout << board[row][col];
            	if (board[row][col] < 10)
					cout << "   ";
            	else
            		cout << "  ";
			}
        }
        cout << endl;
    }
}

bool move(int tile) {
    // illegible number
    if (tile <= 0 && tile >= ver * hor)
        return false;
    
    // find tile and blank - position
    int tr, tc;     // tile row n column
    int br, bc;     // blank row n column
    for (int row = 0; row < ver; row++) {
        for (int col = 0; col < hor; col++) {
            if (board[row][col] == tile) {
                tr = row;
                tc = col;
            } else if (board[row][col] == 0) {
                br = row;
                bc = col;
            }
        }
    }
    
    // check if a valid move, move and break. if not, false
    for (int d = 0; d < direction; d++) {
    	int my = br+possibleMove[d][0];	
    	int mx = bc+possibleMove[d][1];
    	if (my >= 0 && my < ver && mx >= 0 && mx < hor) {	// if not out of the board
	    	if (tr == my && tc == mx) {	// if tile coordinate is one of these possibleMove
	    		swap(board[tr][tc], board[br][bc]);	// swap tile and blank
	    		return true;
			}
		}
	}
	return false;
}

bool win() {
    int value = 1;  //value to check
    for (int row = 0; row < ver; row++) {
        for (int col = 0; col < hor; col++) {
            // if not match
            if (value != board[row][col])
                return false;
            
            // last tile? Win
            if (value == (ver * hor) - 1)
                return true;
            value++;
        }
    }
    return false;
}
