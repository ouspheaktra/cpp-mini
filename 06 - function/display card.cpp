/* CARD */
#include <iostream>
using namespace std;

void card(int number);

main() {
  for (int i = 1; i <= 13; i++) card(i);
}

void card(int number) {
  if (number <= 0 || number > 13) return;
  if (number == 11) number = 'J';
  else if (number == 12) number = 'Q';
  else if (number == 13) number = 'K';
  cout << " _____ \n";
  cout << "|";
  if (number > 10)  cout << (char)number;
  else              cout << number;
  if (number != 10) cout << " ";
  cout << "   |\n";
  cout << "|     |\n";
  cout << "|     |\n";
  cout << "|___";
  if (number != 10) cout << "_";
  if (number > 10)  cout << (char)number;
  else              cout << number;
  cout << "|\n";
}
