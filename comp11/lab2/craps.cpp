/* COMP11
 * Spring 2017
 * Lab 2 Starter Code
 * Craps game (buggy)
 * Bug 1 point == roll 61
 * Bug 2 && 66
   Bug 3 break 43
   Bug 4 <= 70 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// function prototype to roll two dice
int roll_dice();

int main() 
{
	int wallet = 1000;
	bool game_over = false;

	 // Seed the random number generator
	srand((unsigned int)time(NULL));

	while (!game_over) {
		cout << "Enter amount to bet. You have $" << wallet << endl;
		int bet;
		cin >> bet;

		if (bet <= 0)
			cout << "Bet must be positive." << endl;
		else if (bet > wallet)
			cout << "You don't have that much money." << endl;
		else {
			int roll = roll_dice();
			cout << "You rolled " << roll << endl;

			switch (roll) {
			case 7:
				cout << "You win!" << endl;
				wallet += bet;
				break;
			case 2:
			case 3:
			case 12:
				cout << "You lose." << endl;
				wallet -= bet;
				break;
			default:
				// Continue rolling until we roll the point
				// or 7
				int point = roll;
				cout << "The point is " << point << endl;
			do {
					roll = roll_dice();
					cout << "You rolled " << roll << endl;
					if (roll == 7) {
						cout << "You lose." << endl;
						wallet -= bet;
					}
					else if (roll == point) {
						cout << "That matches the point!" <<
							" You win!" << endl;
						wallet += bet;
					}
				} while ((roll != 7) && (roll != point));
			}
		}
		if (wallet <= 0) {
			cout << "You are penniless. Thanks for playing." << endl;
			game_over = true;
		}
		else {
			cout << "Play again? (y/n)" << endl;
			char c;
			cin >> c;
			if (c=='n')
				game_over = true;
		}
		cout << "You ended the game with $" << wallet << endl;
	}


	return 0;
}

// Simulate rolling two dice.  We need a separate call
// to rand() for each die roll to get the same distribution
// as rolling two actual dice.
int roll_dice() {
	return (rand() % 6 + rand() % 6 + 2);
}
