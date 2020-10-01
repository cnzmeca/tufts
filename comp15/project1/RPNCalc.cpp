/*
Christian Zinck
10/13/17
Project1
Member functions and data for RPNCalc class
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>

#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"

using namespace std;

// Default Constructor
RPNCalc::RPNCalc()
{
	stack = DatumStack();
	quit = false;
}

// Destructor
RPNCalc::~RPNCalc()
{
}

// Runs the calculator until quit or eof. Returns void and takes no parameters.
void RPNCalc::run()
{
	string input;
	while (!cin.eof())
	{
		cin >> input;
		handleString(input);
		if (quit == true)
			break;
	}
}

// Handles a command s. Returns void and takes a string.
void RPNCalc::handleString(string s)
{
	int num;
	if (sscanf(s.c_str(), "%d", &num) == 1)
		stack.push(Datum(num));
	else if (s == "#t")
                stack.push(Datum(true));
        else if (s == "#f")
		stack.push(Datum(false));
        else if (s == "not")
	{
        	Datum first = stack.top();
                stack.pop();
                stack.push(Datum(!first.getBool()));
        }
        else if (s == "print")
        	cout << stack.top().toString() << endl;
        else if (s == "clear")
        	stack.clear();
        else if (s == "drop")
        	stack.pop();
        else if (s == "dup")
        	stack.push(stack.top());
        else if (s == "swap")
	{
        	Datum first = stack.top();
                stack.pop();
                Datum second = stack.top();
                stack.pop();
                stack.push(first);
                stack.push(second);
        }
        else if (s == "quit")
        	quit = true;
        else if (s == "file")
		doFile();
	else if (s == "{")
		doCB();
	else if (s == "exec")
		doExec();
	else if (s == "if")
		doIf();
	else
        	handleOperation(s);
}

// Handles an operation op. Returns void and takes a string.
void RPNCalc::handleOperation(string op)
{
	int first = (stack.top()).getInt();
        stack.pop();
        int second = (stack.top()).getInt();
        stack.pop();

	if (op == "+")
        	stack.push(Datum(second+first));
        else if (op == "-")
        	stack.push(Datum(second-first));
        else if (op == "*")
        	stack.push(Datum(second*first));
        else if (op == "/")
        	stack.push(Datum(second/first));
        else if (op == "mod")
        	stack.push(Datum(second%first));
        else if (op == "<")
                stack.push(Datum(second<first));
        else if (op == ">")
        	stack.push(Datum(second>first));
        else if (op == "<=")
        	stack.push(Datum(second<=first));
        else if (op == ">=")
        	stack.push(Datum(second>=first));
        else if (op == "==")
        	stack.push(Datum(second==first));
	else
		cerr << op << ": unimplemented\n";
}

// Does file command. Returns void and takes no parameters.
void RPNCalc::doFile()
{
        ifstream infile;
        string filename;
        cin >> filename;
        infile.open(filename.c_str());

        if (!infile.is_open())
        	cerr << "Unable to read " << filename << endl;
	else
	{
        	string fs;
        	for (infile >> fs; !infile.eof(); infile >> fs)
        	{
        		handleString(fs);
                	if (quit == true)
                		return;
        	}
	}
}

// Pushes command block. Returns void and takes no parameters
void RPNCalc::doCB()
{
	int numUnclosedBraces = 1;
        string result = "";

        string cbs;
        for (cin >> cbs; !cin.eof(); cin >> cbs)
        {
                if (cbs == "{")
		{
                        numUnclosedBraces++;
		}
		else if (cbs == "}")
                {
                        numUnclosedBraces--;
                        if (numUnclosedBraces == 0)
                                break;
                }
		result = result + cbs + " ";
        }
	stack.push(Datum(result));
}

// Does exec command. Returns void and takes no parameters.
void RPNCalc::doExec()
{
	if (!stack.top().isCodeBlock())
        {
        	cerr << "Error: cannot execute non codeblock\n";
        }
        else
        {
        	string cb = stack.top().getCodeBlock();
        	istringstream iss(cb);

		string cbs;
                while (iss >> cbs)
			handleString(cbs);
        }
}

// Does if command. Returns void and takes no parameters.
void RPNCalc::doIf()
{
	string first, second;
        bool third;
        if (!stack.top().isCodeBlock())
        {
        	cerr << "Error: expected codeblock in if branch\n";
                return;
        }
        else
        	first = stack.top().getCodeBlock();
        stack.pop();

        if (!stack.top().isCodeBlock())
        {
        	cerr << "Error: expected codeblock in if branch\n";
        	return;
        }
        else
                second = stack.top().getCodeBlock();
        stack.pop();

        if (!stack.top().isBool())
        {
        	cerr << "Error: expected boolean in if test\n";
                return;
        }
        else
        	third = stack.top().getBool();
        stack.pop();

        if (third)
        	handleString(second);
        else
        	handleString(first);
}
