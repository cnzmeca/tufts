/*
Christian Zinck
Project 2
11/17/17
String Processor Implementation
*/

#include <iostream>
#include <string>

#include "stringProcessing.h"
using namespace std;

// Returns a string that is the input string without leading and trailing
// nonalphanumeric characters
string stripNonAlphaNum(string word)
{
	int start = 0, end = 0;
	string rString = "";
	int length = word.length();

	// Finds first alphanum character
	for (int i = 0; i < length; i++)
	{
		if ((word[i]>=48 && word[i]<=57)||(word[i]>=65 && word[i]<=90)
		||(word[i]>=97 && word[i]<=122))
		{
			start = i;
			break;
		}
	}
	// Finds last alphanum character
	for (int i = length-1; i >= 0; i--)
	{
		if ((word[i]>=48 && word[i]<=57)||(word[i]>=65 && word[i]<=90)
		||(word[i]>=97 && word[i]<=122))
		{
			end = i;
			break;
		}
	}
	// Trims non alphanum ends
	rString = word.substr(start, end - start + 1);
	return rString;	
}
