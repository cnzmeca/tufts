#include <iostream>
using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

class Board
{	
private:
	// Game board
	int **array;
	// Size of game board
	int size;
	// Score of current game
	int score;
public:
	// Default constructor
	Board();
	// Parametrized constructor to allow user to set size
	Board(int);
	// Destructor
	~Board();	
	
	// Sets up the board. No input or output
	void setupBoard();
	// Moves the board in a direction based off of the wasd input. No return
	void moveBoard(char);
	// Displays the board. No inputs or outputs
	void printBoard();
	// Increases the current score by the int input. No return
	void incScore(int);
	// Takes an x,y position and value assign that position. No return
	void setElement(int, int, int);	

	// Returns current score. No input
	int getScore();	
	// Returns the size of the board. No input
	int getSize();
	// Returns the element of array at position determined by int inputs
	int getElement(int,int);
	
	// Decides if the game is over. No input. Returns true or false	
	bool gameOver();
};

#endif
