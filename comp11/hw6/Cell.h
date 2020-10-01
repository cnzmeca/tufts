//Signed off my Matt Shenton April 12
#include <iostream>
using namespace std;

#ifndef CELL_H_
#define CELL_H_

class Cell
{
private:
	// The number that the cell will display on the board
	int value;
	
public:
	// Default constructor
	Cell();
	// Parametrized constructor for creating 4 squares
	Cell(int);
	// Parametrized constructor for combining 2 cells
	Cell(int, int);
	
	// Returns the value of a cell object. No input
	int getValue();
};
#endif
