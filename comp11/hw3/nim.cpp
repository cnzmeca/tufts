/*
Christian Zinck
COMP11
HW 3
Programming #2
February 18, 2017
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	//Creates random seed
        srand(time(NULL));	
	
	//Creates variables, sets some = 0
	int player1Score, player2Score, player1Guess, playerTurn;
	player1Score = player2Score = player1Guess = 0;

	//Gets players guess for coin flip
	do
	{
		cout << "There will be a coin flip to decide who goes first." <<
		endl << "Enter 1 for heads and 2 for tails." << endl;
		cin >> player1Guess;
	} while (player1Guess < 1 || player1Guess > 2);
	
	//Decides who wins coin flip
	int coinFlip = rand() % 2 + 1;
	if (player1Guess == coinFlip)
		playerTurn = 1;
	else
		playerTurn = 2;
	
	//Main game loop
	for (int i = 0; i < 3; i++)
	{
		cout << "Player " << playerTurn << " will go first." << endl;
		int numBeans = rand() % 26 + 5;
		
		//Game continues when there are beans
		while (numBeans != 0)
		{
			//Player 1 turn
			if (playerTurn == 1)
			{
				int player1Take = 0;
				//Gets legal input for player1Take
				do
				{	
					cout << "There are " << numBeans << 
		". How many beans will you take?" <<						 endl;
					cin >> player1Take;
				} while (player1Take < 1 ||
				player1Take > 3 || player1Take > numBeans);
				
				//Takes player1Take beans
				cout << "You took " << player1Take <<
				 " beans. There are " << 
				(numBeans-player1Take)  << " left." << endl;
				numBeans = numBeans - player1Take;
				playerTurn = 2;
			}

			//Player 2 turn
			else if (playerTurn == 2)
			{
				int player2Take;
				//Sets player2Take to a random legal value
				if (numBeans < 4)
					player2Take = rand() % numBeans + 1;
				else
					player2Take = rand() % 3 + 1;

				//Takes player2Take beans
                        	cout << "I took " << player2Take <<
				 " beans. There are " <<
				(numBeans-player2Take) << " left." << endl;
				numBeans = numBeans - player2Take;
				playerTurn = 1;
			}
		}

		//Assigns point to round winner
		if (playerTurn == 2)
		{
			cout << "Player 2 wins this round." << endl;
			player2Score++;
		}
		else if (playerTurn == 1)
		{
			cout << "Player 1 wins this round." << endl;
			player1Score++;
		}
	}
	
	//Prints final score and game winner
	cout << "Final score:" << endl << "Player 1: " << player1Score <<
	 " 	Player 2: " << player2Score << endl;
	if (player1Score > player2Score)
                {       
                        cout << "Player 1 wins!" << endl;
                }
        else
                {       
                        cout << "Player 2 wins!" << endl;
                }
}
