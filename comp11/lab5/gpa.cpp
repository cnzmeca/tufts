/* COMP11
 * 3/15/17
 * Christian Zinck
 * Converting grades to GPAs */

#include <iostream>
#include <fstream>
using namespace std;

const int MAX = 50;

int main()
{
	// Variables for the filestream
	// and num classes the student has taken
	ifstream infile;
	int num_classes = 0;
	double gpas[MAX];
	int studentNum;

	// Decides which student's file to access	
	do
	{
		cout << "Choose a student" << endl;
		cin >> studentNum;
	} while (studentNum < 1 || studentNum > 3);
	
	// Accesses correct file
	switch (studentNum)
	{
		case 1 : 
			infile.open("studentone.txt");	
			break;
		case 2 :
                	infile.open("studenttwo.txt");
                	break;
		case 3 :
                	infile.open("studentthree.txt");
                	break;
	}
	
	// Tests if file is open
	if (!infile.is_open())
	{
    		cerr << "Error opening file\n";
    		return 1;
	}
	
	
	int count = 0;
	// Runs until end of file or more than MAX classes
	while(!infile.eof() && count < 2 * MAX )	
	{
		string line;
		infile >> line;
		// Only takes grades and converts from string to double value
		if ((count + 2)%2 == 1)
		{
			if (line == "A+")
				gpas[count/2] = 4.0;
			else if (line == "A")
				gpas[count/2] = 4.0;
			else if (line == "A-")
				gpas[count/2] = 3.67;
			else if (line == "B+")
				gpas[count/2] = 3.33;
			else if (line == "B")
				gpas[count/2] = 3.0;
			else if (line == "B-")
				gpas[count/2] = 2.67;
		}
		count++;	
	}
	
	// Closes file
	infile.close();
	
	// Calculates num_classes
	num_classes = (count-1)/2;
	
	// Now the array is populated with doubles.
	// Calculate the average GPA of the student.
	double avg_gpa, total = 0.0;
	for (int i = 0; i < num_classes; i++)
	{
		total += gpas[i];
	}
	avg_gpa = total / num_classes;
	cout << "The student's GPA is " 
		 << avg_gpa << endl;

	return 0;
}
