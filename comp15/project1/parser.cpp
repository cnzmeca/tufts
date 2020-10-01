#include <iostream>

using namespace std;

string parseCodeBlock(istream &input)
{
	int numOpenBraces = 0;
	int numClosedBraces = 0;
	string result = "";

	string x;
	for (input >> x;(!input.eof());input >> x)
	{
		if (x == "{")
		{
			numOpenBraces++;
			if (numOpenBraces != 1)
				result = result + x;
		}
		else if (x == "}")
		{
			numClosedBraces++;
			if (numClosedBraces != numOpenBraces)
				result = result + " " + x;
			else
				break;
		}
		else
			result = result + " " + x;
	}
	return result; 
}

/*
int main()
{
	cout << parseCodeBlock(cin) << endl;
}
*/
