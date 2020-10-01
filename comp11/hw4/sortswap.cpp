/*
Christian Zinck
COMP11
HW 4
Programming #1
March 9, 2017
*/        
         
#include <iostream>
using namespace std;

//swap prototype
void swap(int &, int &);

int main()
{
	//Gets 4 ints from user
	int num1, num2, num3, num4;
	cout << "Enter 4 integers:" << endl;
	cin >> num1;
	cin >> num2;
	cin >> num3;
	cin >> num4;

	//Executes swap for all necessary pairs
	swap(num1,num2);
	swap(num1,num3);
	swap(num1,num4);
        swap(num2,num3);
	swap(num2,num4);
	swap(num3,num4);

	//Displays ordered nums
	cout << "" << num1 << " " << num2 << " " << num3 << " " << num4 << endl;
	return 0;
}

//Swaps the value of two numbers if the first is larger
void swap(int &num1, int &num2)
{
	if (num1 > num2)
	{
		int temp = num1;
		num1 = num2;
		num2 = temp;
	}
}
