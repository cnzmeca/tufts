/*
Christian Zinck
10/13/17
Project 1
Definition for DatumStack class
*/

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <iostream>

#include "Datum.h"

using namespace std;

class DatumStack
{
	public:
		DatumStack();
		DatumStack(Datum arr[], int length);
		~DatumStack();

		bool isEmpty();
                void clear();
                int size();
                Datum top();
                void pop();
                void push(Datum d);

		struct DatumElement
                {
                        Datum element;
			
			DatumElement() : element(Datum(0))
			{}
                        DatumElement(Datum d) : element(d)
			{}
			~DatumElement()
			{}
                };

                //void print(); //commented out for submitting
        private:
		int count;
		int capacity;
		DatumElement *s;
		
		//void expand();
		void print(); //commented out for testing
};

#endif
