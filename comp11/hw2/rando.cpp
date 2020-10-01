/*
Christian Zinck
COMP11
HW 2
Programming #1
February 9, 2017
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	//Generates 2 random ints
	srand(time(NULL));
	int num1 = rand()%10 + 5;
	int num2 = rand()%10 + 5;
	int numWrong = 0;
	//Asks user for the sum of the ints until they guess wrong twice
	while (numWrong < 2)
	{
		//Asks user for sum
		cout << "What is " << num1 << " + " << num2 << "?" << endl;
		int ans;
		cin >> ans;
		//If user is right
		if (ans == (num1 + num2))
		{
			cout << "Correct! Gameover." << endl;
			break;
		}
		//If user has another guess
		else if (numWrong == 0)
	        {
			cout << "Incorrect! Try again." << endl;
                        numWrong++;
       		}
		//If user has no more guesses
		else
		{
			cout << "Game over... You lose." << endl;
			numWrong++;
		}
	}
	return 0;
}
