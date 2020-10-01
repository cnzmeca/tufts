#include "Board.h"
#include <iostream>
using namespace std;

// Default constructor
Board::Board()
{
	array = NULL;
	size = 4;
	score = 0;	
}

// Parameterized constructor to set size
Board::Board(int num)
{
	array = NULL;
	size = num;
	score = 0;
}

// Destructor
Board::~Board()
{
	for (int row = 0; row < size; row++)
		delete[] array[row];
	delete[] array;
}

// Sets up board with 2 tiles of value 2
void Board::setupBoard()
{
	array = new int*[size];
	for (int row = 0; row < size; row++)
		array[row] = new int[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			array[i][j] = 0;
		}
	}
	array[1][0] = 2;
	array[0][1] = 2;
}

// Moves board in desired direction
void Board::moveBoard(char dir)
{
	switch(dir)
	{
	// Up case
	case 'w':
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				for (int k = j+1; k < size; k++)
				{
					if (array[k][i] == array[j][i])
					{
						incScore(2*array[j][i]);
                                        	array[j][i] = 2*array[j][i];
                                        	array[k][i] = 0;
						break;
					}
					else if (array[k][i] != 0)
					{
						break;
					}
				}
			}
			int count = 0;
			for (int j = 0; j < size; j++)
			{
				if (array[j][i] != 0)
				{
					array[count][i] = array[j][i];
					if (count != j)
						array[j][i] = 0;
					count++;
				}
			}
                }
	break;
	
	// Down case
	case 's':
                for (int i = 0; i < size; i++)
                {
                        for (int j = size - 1; j > 0; j--)
                        {       
                                for (int k = j-1; k >= 0; k--)
                                {
                                        if (array[k][i] == array[j][i])
                                        {
                                                incScore(2*array[j][i]);
                                                array[j][i] = 2*array[j][i];
                                                array[k][i] = 0;
                                                break;
                                        }
                                        else if (array[k][i] != 0)
                                        {
                                                break;
                                        }
                                }
                        }
                        int count = size - 1;
                        for (int j = size - 1; j >= 0; j--)
                        {
                                if (array[j][i] != 0)
                                {
                                        array[count][i] = array[j][i];
                                        if (count != j)
                                                array[j][i] = 0;
                                        count--;
                                }
                        }
                }
        break;
	
	// Left case
	case 'a':
                for (int i = 0; i < size; i++)
                {
                        for (int j = 0; j < size - 1; j++)
                        {
                                for (int k = j+1; k < size; k++)
                                {
                                        if (array[i][k] == array[i][j])
                                        {
                                                incScore(2*array[i][j]);
                                                array[i][j] = 2*array[i][j];
                                                array[i][k] = 0;
                                                break;
                                        }
                                        else if (array[i][k] != 0)
                                        {
                                                break;
                                        }
                                }
                        }
                        int count = 0;
                        for (int j = 0; j < size; j++)
                        {
                                if (array[i][j] != 0)
                                {
                                        array[i][count] = array[i][j];
                                        if (count != j)
                                                array[i][j] = 0;
                                        count++;
                                }
                        }
                }
        break;
	
	// Right case
	case 'd':
                for (int i = 0; i < size; i++)
                {
                        for (int j = size - 1; j > 0; j--)
                        {
                                for (int k = j-1; k >= 0; k--)
                                {
                                        if (array[i][k] == array[i][j])
                                        {
                                                incScore(2*array[i][j]);
                                                array[i][j] = 2*array[i][j];
                                                array[i][k] = 0;
                                                break;
                                        }
                                        else if (array[i][k] != 0)
                                        {
                                                break;
                                        }
                                }
                        }
                        int count = size - 1;
                        for (int j = size - 1; j >= 0; j--)
                        {
                                if (array[i][j] != 0)
                                {
                                        array[i][count] = array[i][j];
                                        if (count != j)
                                                array[i][j] = 0;
                                        count--;
                                }
                        }
                }
        break;
	}	
}

// Prints board
void Board::printBoard()
{
	cout << "Current score: " << score << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (array[i][j] != 0)
				cout << array[i][j] << "\t";
			else
				cout << "X\t";
		}
		cout << endl;
	}
	cout << endl;
}

// Increases score by provided amount
void Board::incScore(int amt)
{
	score += amt;
}

// Sets element (x,y) equal to val
void Board::setElement(int x, int y, int val)
{
	array[x][y] = val;
}

// Returns score
int Board::getScore()
{
	return score;
}

// Returns size
int Board::getSize()
{
	return size;
}

// Returns element (x,y)
int Board::getElement(int x, int y)
{
	return array[x][y];
}

// Decides if game is over
bool Board::gameOver()
{
	// Loops through all elements
	for (int i = 0; i < size; i++)
        {
                for (int j = 0; j < size; j++)
                {
			// Checks for open spaces
                        if (array[i][j] == 0)
                       		return false;
			// Checks for equivalence to adjacent elements
			if (i != 0)
			{
				if (array[i][j] != array[i-1][j])
					return false;
			}
			if (i != size)
                        {
                                if (array[i][j] != array[i+1][j])
                                        return false;
                        }
			if (j != 0)
                        {
                                if (array[i][j] != array[i][j-1])
                                        return false;
                        }
                        if (j != size)
                        {
                                if (array[i][j] != array[i][j+1])
                                        return false;
                        }
		}
	}
	return true;
}
