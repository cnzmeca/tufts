/*
Christian Zinck
COMP11
HW 1
Programming #2
February 2, 2017
*/
#include <iostream>
using namespace std;

int main()
{
	//Stores user input in age
	cout << "How old are you?" << endl;
	int age;
	cin >> age;
	//Calculates hours alive
	int hoursAlive = 8760 * age;
	cout << "You have been alive for " << hoursAlive << " hours!" << endl;
	return 0;
}
