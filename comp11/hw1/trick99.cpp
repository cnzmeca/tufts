/*
Christian Zinck
COMP11
HW 1
Programming #3
February 2, 2017
*/
#include <iostream>
using namespace std;

int main()
{
	//Creates several variables used in following calculations
	int player1, player2, factor, answer;
	//Gets input from player 1
	cout << "Player 1, enter a number between 10 and 49." << endl;
	cin >> player1;
	//Gets input from player 2
	cout << "Player 2, enter a number between 50 and 99." << endl;
	cin >> player2;
	//Calculates factor
	factor = 99 - player1;
	//Adds the factor and player 2's number
	answer = player2 + factor;
	//Removes the hundreds digit and adds it to the unit's digit
	answer -= 99;
	//Subtracts answer from player 2's number
	answer = player2 - answer;
	//Prints result
	cout << "The answer is " << answer << ". Player 1 was right!" << endl;
	return 0;
}
