/*
Christian Zinck
HW 5
11/2/17
Main file for sorting algorithms
*/

#include "sortAlgs.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
	
	// Data	
	vector<string> args;
	for (int i = 0; i < argc; i++)
		args.push_back(argv[i]);	
	
	vector<int> vec;
	string listOrigin;
	string sortAlg;
	
	// Checks for correct arg count
	if (argc == 4)
	{
		listOrigin = args[3];
		ifstream infile;
		infile.open(argv[3]);
		if (!infile.is_open())
        	{
                	cerr << "Failed to open file." << endl;
                	return 1;
        	}
		int num;
		for (infile >> num; (!infile.eof()); infile >> num)
                	vec.push_back(num);
        	infile.close();
	}
	else if (argc == 3)
	{
		listOrigin = "cin";
		int num;
		for (cin >> num; (!cin.eof()); cin >> num)
                        vec.push_back(num);
	}
	else
	{
		cerr << "Usage:  sorter sortAlg outputMode [fileName]\n"
			"\twhere:  sortAlg is -s1, -s2, or -s3\n"
                        "\tand     outputMode is --print or --save\n" << endl;
		return 1;
	}
	
	// Checks for valid sort method
	if (args[1] == "-s1")
	{
		insertionSort(vec);
		sortAlg = "1";
	}
	else if (args[1] == "-s2")
	{
		mergeSort(vec);
		sortAlg = "2";
	}
	else if (args[1] == "-s3")
	{
		quickSort(vec);
		sortAlg = "3";
	}
	else
	{
		cerr << "Usage:  sorter sortAlg outputMode [fileName]\n"
                        "\twhere:  sortAlg is -s1, -s2, or -s3\n"
                        "\tand     outputMode is --print or --save\n" << endl;
		return 1;
	}
	
	// Checks for valid output method
	if (args[2] == "--print")
	{
		for (size_t i = 0; i < vec.size(); i++)
			cout << vec[i] << endl;
	}
	else if (args[2] == "--save")
	{
		stringstream ss;
		ss << vec.size();
		string numElements;
		ss >> numElements; 
		string filename = listOrigin + "_" + sortAlg + "_" + numElements
		+ "_sorted.txt";

		ofstream outfile;
		outfile.open(filename.c_str());
		for (size_t i = 0; i < vec.size(); i++)
			outfile << vec[i] << endl;
		outfile.close();
	}
	else
	{
		 cerr << "Usage:  sorter sortAlg outputMode [fileName]\n"
                        "\twhere:  sortAlg is -s1, -s2, or -s3\n"
                        "\tand     outputMode is --print or --save\n" << endl;
	}
}
