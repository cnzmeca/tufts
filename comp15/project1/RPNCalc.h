/*
Christian Zinck
10/13/17
Project 1
Definition for RPNCalc class
*/

#ifndef RPNCALC_H
#define RPNCALC_H

#include <iostream>

#include "Datum.h"
#include "DatumStack.h"

using namespace std;

class RPNCalc
{
	public:
		RPNCalc();
		~RPNCalc();

		void run();
	private:
		DatumStack stack;
		bool quit;
	
		void handleString(string s);
		void handleOperation(string op);
		void doFile();
		void doCB();
		void doExec();
		void doIf();
};

#endif

