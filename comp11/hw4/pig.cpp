/* COMP11
 * Spring 2017
 * HW4 (PIG game)
 * Starter Code */

#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

// Function prototype: check_for_win
int check_for_win(int, int);
// Function prototype: end_round
int end_round(int, int &, int &, int);
// Function prototype: roll_die
int roll_die();

// Number of points needed to win
const int THRESHOLD = 20;

int main () 
{
	// Seed the random variable
	srand(time(NULL));

	// Total number of points for each player.
	int pone_points = 0, ptwo_points = 0;

	// Whose turn it is. Player One always starts.
	int turn = 1;

	// Is the game over yet
	bool game_over = false;

	// While loop for the game. A game comprises several rounds.
	while( !game_over )
	{
		// Announce whose turn it is
		cout << "Player " << turn << " is up!\n";

		// Round-specific variables
		bool round_over = false;
		int round_points = 0;
		int check;
		int roll;
		
		// Player rolls until a 1 or a hold
		do
		{
			// Checks that input is 0 or 1
			do
			{
			cout << "Enter '0' for roll or '1' for hold." << endl;
			cin >> check;
			} while (check != 0 && check != 1);
			
			// Rolls if player rolls
			if (check == 0)
			{
				// Calls roll_die
				roll = roll_die();
				
				// Displays roll
				cout << "You rolled a " << roll << endl;
				
				// Adds points to round_points if 1 not rolled
				if (roll != 1)
				{
					round_points += roll;
					cout << "Round points: " <<
					round_points << endl;
				}
				// Ends round and resets points if 1 is rolled
				else
				{
					round_over = true;
					round_points = 0;
					cout << "End of round." << endl;
				}
			}
			// Banks round_points if player holds
			else
			{
				round_over = true;
				cout << "You banked " << round_points <<
				" points. End of round." << endl;
			}
		} while (round_over == false);
		

		// Ends round
		turn = end_round(turn, pone_points, ptwo_points, round_points);
		
		// Displays score
		cout << "Player 1: " << pone_points << "	Player 2: " <<
		ptwo_points << endl;
		
		// Ends game
		if (check_for_win(pone_points, ptwo_points) == 1)
		{
			cout << "Player 1 wins" << endl;
			game_over = true;
		}
		else if (check_for_win(pone_points, ptwo_points) == 2)
		{
			cout << "Player 2 wins" << endl;
			game_over = true;
		}
	} // end game while loop

	// Game is over. End the program.
	cout << "Thanks for playing!\n";
	return 0;
}

//Simulates the rolling of a die
int roll_die()
{
	return rand() % 6 + 1;
}


/****************************************
 * NO NEED TO MODIFY CODE BELOW THIS POINT    *
 ****************************************/

// FUNCTION DEFINITION
// Function check_for_win
// Arguments:
//	Player 1 and 2's points (ints)
// Returns:
//	0 is game is not over
// 	1 if player one won
// 	2 if player two won
// Does:
// 	Compares each score to the threshold
int check_for_win(int pone_points, int ptwo_points)
{
	// Check the players' current points against the threshold
	if( pone_points >= THRESHOLD ) 
	{			
		return 1;
	}
	else if( ptwo_points >= THRESHOLD )
	{
		return 2;
	}	
	
	// If we didn't meet either condition,
	// then nobody won
	return 0;
}

// FUNCTION DEFINITION
// Function end_round
// Arguments:
// 	1. whose turn it is (int)
//	2. player one's points (int, by ref)
// 	3. player two's points (int by ref)
// 	4. round points (int)
// Returns:
//	# of updated turn
// Does:
//	Updates p1 and p2 points
//	Switches whose turn it is
int end_round(int turn, int &pone_points, int &ptwo_points, int round_points)
{
	if(turn == 1)
	{
		pone_points += round_points;
		return 2;
	}
	else{
		ptwo_points += round_points;
		return 1;
	}

}
