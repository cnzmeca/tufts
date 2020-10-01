/*
Christian Zinck
COMP11
HW 1
Programming #1
February 2, 2017
*/
#include <iostream>
using namespace	std;

int main()
{
	//Two variables to help sum the user input 
	int total = 0,input = 0;
	//Getting eight ints from the user
 	for(int i = 0; i < 8; i++)
   	{
     		cout << "Input a number." << endl;
     		cin >> input;
		//Running total of ints
     		total += input;
   	}
	cout << "The total is: " << total << "." << endl;
 	return 0;
}
