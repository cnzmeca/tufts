/*
Christian Zinck
COMP11
HW 2
Programming #2
February 9, 2017
*/

/*
Test 1 -
	In: tom, kim, bob
	Out: bob, kim, tom
Test 2 - 
	In: cat, dog, car
	Out: car, cat, dog
Test 3 -
	In: c, a, b
	Out: a, b, c


*/
#include <iostream>
using namespace std;

int main()
{
	string in1, in2, in3, out1, out2, out3;
	cout << "Please use all lowercase letters." << endl;
	cout << "Enter the first word." << endl;
	cin >> in1;
	cout << "Enter the second word." << endl;
        cin >> in2;
	cout << "Enter the third word." << endl;
        cin >> in3;
	if (in1 < in2)
	{
		if (in2 < in3)
		{
			out1 = in1;
			out2 = in2;
			out3 = in3;
		}
		else if (in1 < in3)
		{
			out1 = in1;
			out2 = in3;
			out3 = in2;
		}
		else
		{
			out1 = in3;
			out2 = in1;
			out3 = in2;
		}
	}
	else
	{
		if (in1 < in3)
                {
                        out1 = in2;
                        out2 = in1;
                        out3 = in3;
                }
                else if (in2 < in3)
                {
                        out1 = in2;
                        out2 = in3;
                        out3 = in1;
                }
                else 
                {
                        out1 = in3;
                        out2 = in2;
                        out3 = in1;
		}	
	}
	cout << "Your words in alphabetical order:" << endl << out1 << ", " << out2 << ", " << out3 << endl;
	return 0;
}
