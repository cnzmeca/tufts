/*
Christian Zinck
COMP11
HW 4
Programming #2
March 9, 2017
*/

#include <iostream>
using namespace std;

//Average prototype
double average(int [5]);

int main()
{
	//Gets 5 ints from user and stores in array
	cout << "Enter 5 integers:" << endl;
	int nums[5];
	for (int i = 0; i < 5; i++)
	{
		cin >> nums[i];
	}
	//Calls average on nums array
	double avg = average(nums);
	//Prints average
	cout << avg << endl;
	return 0;
}

//Averages nums array
double average(int nums[5])
{
	int total = 0;
	//Adds up all numbers
	for (int i = 0; i < 5; i++)
	{
		total += nums[i];
	}
	//Returns average
	return (total*1.0)/5;
}
