#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
main() {
	string dice_roll[] = {"\
   _________\n\
  /        /\\\n\
 /  O  O  /  \\\n\
/________/ OO \\\n\
\\        \\ OO /\n\
 \\   O    \\  /\n\
  \\________\\/", "\
   _________\n\
  /\\        \\\n\
 /  \\   O    \\\n\
/ O  \\________\\\n\
\\  O /      O /\n\
 \\  /   O    /\n\
  \\/_O______/"};
  
	string dice[] = {"", "\
  __________\n\
 /________ /|\n\
|         | |\n\
|         | |\n\
|    O    | |\n\
|         | |\n\
|_________|/", "\
  __________\n\
 /________ /|\n\
|         | |\n\
|  O      | |\n\
|         | |\n\
|      O  | |\n\
|_________|/", "\
  __________\n\
 /________ /|\n\
|         | |\n\
|  O      | |\n\
|    O    | |\n\
|      O  | |\n\
|_________|/", "\
  __________\n\
 /________ /|\n\
|         | |\n\
|  O   O  | |\n\
|         | |\n\
|  O   O  | |\n\
|_________|/", "\
  __________\n\
 /________ /|\n\
|         | |\n\
|  O   O  | |\n\
|    O    | |\n\
|  O   O  | |\n\
|_________|/", "\
  __________\n\
 /________ /|\n\
|         | |\n\
|  O   O  | |\n\
|  O   O  | |\n\
|  O   O  | |\n\
|_________|/"};

	srand(time(NULL));
	
	int time;		// times to roll the dice for each user
	int amount;		// number of dices to roll per time
	string name;	// store the user's name
	
	// welcome screen, ask to input anything
	system("color a4");
	cout << " --- ROLLING THE DICE ---" << endl << endl;
	cout << " --- YOU VS COMPUTER  ---" << endl << endl;
	cout << dice_roll[1] << endl << endl;
	cout << endl << "Your Name :" << endl; cin >> name;
	cout << endl << "How many Dices ?" << endl; cin >> amount;
	cout << endl << "How many Times ?" << endl; cin >> time;
	Sleep(500);
	cout << endl << "Press Enter to START";
	cin.ignore(); cin.ignore();
	system("cls");
	
	// point
	int my_point[time*amount];
	int sum_my_point = 0;
	int pc_point[time*amount];
	int sum_pc_point = 0;
	
	int id = 0;		// id to use in my_point or pc_point
	
	// roll six times
	for (int t = 0; t < time*2; t++) {
		
		if (t == time)	id = 0;		// reset id, for pc_point
		
		// temporary point, to use in each round
		int point[amount];
		// generate point
		for (int i = 0; i < amount; i++) {
			point[i] = rand()%6+1;
			// user's point
			if (t < time) {
				my_point[id++] = point[i];
				sum_my_point += point[i];
			// pc's point
			} else {
				pc_point[id++] = point[i];
				sum_pc_point += point[i];
			}
		}
		
		// color the terminal
		if (t < time)	system("color f0");
		else 			system("color 0f");
		
		// show dice image, 6 randomly and last one is the result
		for (int i = 0; i <= 7 ;i++) {
			system("cls");	// clear screen
			
			// whose turn?
			if (t < time)	cout << " --- YOUR TURN (" << name << ") ---" << endl;
			else 			cout << " --- COMPUTER's TURN ---" << endl;
				
			// if it is the last one, display dices indicate the point
			if (i == 7) {
				for (int j = 0; j < amount; j++)
					cout << dice[point[j]] << endl << endl;
				break;
			}
			
			// show dice randomly
			for (int j = 0; j < amount; j++)
				if (i % 2)	cout << dice[rand()%6+1] << endl << endl;
				else		cout << dice_roll[rand()%2] << endl << endl;
			
			Sleep(200);	// delay 200
		}
		
		// show more information for user
		if (t < time) {
			cout << "You get";
			// user's point
			for (int i = 0; i < amount; i++)
				cout << "   " << point[i];
			// message : press enter to continue
			if (t == time-1)	cout << endl << "Press Enter for COMPUTER's TURN";
			else				cout << endl << "Press Enter to ROLL AGAIN";
			// press enter to continue
			cin.ignore();
		
		// show more information for pc
		} else {
			cout << "Computer gets ";
			// pc's point
			for (int i = 0; i < amount; i++)
				cout << "   " << point[i];
			// delay
			Sleep(1500);
		}
	}
	
	system("cls");
	
	cout << " --- LIST ALL POINT --- " << endl << endl;
	
	// display the result
	for (int i = 0; i < time*2; i++) {
		Sleep(150);
		
		// whose point?
		if (i == 0)			cout << name << "'s Point : " << endl;
		else if (i == time)	cout << "Computer's Point : " << endl;
		
		// round
		cout << "\tRound ";
		int idd =  i < time ? i : i - time;
		cout << idd + 1;
		
		// point
		cout << " :";
		for (int j = 0, l = amount-1; j <= l; j++) {
			cout << "   ";
			if (i < time)	cout << my_point[idd*amount + j];
			else 			cout << pc_point[idd*amount + j];
		}
		cout << endl;
		
		// display total point
		if (i == time-1)	cout << name << "'s Total Point is " << sum_my_point << endl << endl;
		if (i == time*2-1)	cout << "Computer's Total Point is " << sum_pc_point << endl << endl;
	}
	Sleep(500);
	
	// WHO'S THE WINNER
	cout << " --- THE" << endl; Sleep(500);
	cout << " --- WINNER" << endl; Sleep(500);
	cout << " --- IS" << endl; Sleep(500);
	if (sum_my_point == sum_pc_point)		cout << " --- NO ONE --- IT'S DRAW ---";
	else if (sum_my_point > sum_pc_point)	cout << " --- " << name <<" ---";
	else									cout << " --- COMPUTER ---";	
		
	// flash
	for (int i = 0;;i++) {
		if (i % 2)	system("color b4");
		else		system("color a5");
		Sleep(200);
	}
}
