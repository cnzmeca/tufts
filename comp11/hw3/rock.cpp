/*
Christian Zinck
COMP11
HW 3
Programming #1
February 18, 2017
*/

#include <iostream>
using namespace std;

int main()
{
	//Creates score totals for each player
	int player1Score = 0, player2Score = 0;
	
	//Main game loop
	for (int i = 0; i < 3; i++)
	{
		cout << "Round " << (i+1) << endl;
		
		//Gets input from players
		char player1Pick, player2Pick;
		do
                {
			cout << "Player 1, enter 'R' for rock, 'S' for scissors, or 'P' for paper." << endl;
			cin >> player1Pick;
		} while (player1Pick != 'R' && player1Pick != 'S' && player1Pick != 'P');
		do
                {
                        cout << "Player 2, enter 'R' for rock, 'S' for scissors, or 'P' for paper." << endl;
                        cin >> player2Pick;
                } while (player2Pick != 'R' && player2Pick != 'S' && player2Pick != 'P');
		
		//Logic to decide who gets the point and wins the round
		//Checks every possible combination of R, S, and P
		if (player1Pick == 'R')
        	{
               		if (player2Pick == 'S')
			{
                        	player1Score++;
                		cout << "Player 1 wins this round." << endl;
			}
			else if (player2Pick == 'P')
                        {
				player2Score++;
        			cout << "Player 2 wins this round." << endl;
			}
			else
                        	cout << "This round is a tie." << endl;
		}
        	else if (player1Pick == 'S')
        	{
                	if (player2Pick == 'P')
                        {
				player1Score++;
                		cout << "Player 1 wins this round." << endl;
			}
			else if (player2Pick == 'R')
                        {
				player2Score++;
        			cout << "Player 2 wins this round." << endl;
			}
			else
                        	cout << "This round is a tie." << endl;
		}
        	else if (player1Pick == 'P')
        	{
                	if (player2Pick == 'R')
			{
                        	player1Score++;
                		cout << "Player 1 wins this round." << endl;
			}
			else if (player2Pick == 'S')
                        {
				player2Score++;
				cout << "Player 2 wins this round." << endl;
			}
			else
                        	cout << "This round is a tie." << endl;
        	}
	}
	
	//Prints final score and winner(or tie)
	cout << "Final score:" << endl << "Player 1: " << player1Score << "	Player 2: " << player2Score << endl;
	if (player1Score > player2Score)
		cout << "Player 1 wins!" << endl;
	else if (player2Score > player1Score)
		cout << "Player 2 wins!" << endl;
	else
		cout << "It's a tie!" << endl;
}
