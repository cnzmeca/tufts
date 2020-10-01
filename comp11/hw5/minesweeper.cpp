/*
Christian Zinck
COMP11
HW 5
Programming #1
March 17, 2017
*/

/*
I used 4 strategies to test and validate my program. I decreased the size of the
grid to make testing go faster. Instead of randomly generating the grid I
hardcoded it in so I would know where the mines are. I used a lot of cout lines
to make sure my variables had the values I wanted them to have at certain times.
Finally I tested my functions individually by calling them by themselves in the
main function.
*/

#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

// constants
const int DIMEN = 9;
const int MAX_MINES = 50;
const char MINE = 'x';
const char UNSEEN = '-';

// function prototypes
void print_board(char [][DIMEN]);
void populate_plain_board(char [][DIMEN]);
void populate_mines_board(char [][DIMEN]);
bool win(char [][DIMEN], char [][DIMEN]);
bool lose(char [][DIMEN], int, int);
void replace(char [][DIMEN], char [][DIMEN], int, int);

int main()
{
	srand(time(NULL));
	
	// Creates boards
	char user_board[DIMEN][DIMEN];
	char mines[DIMEN][DIMEN];
	
	// Populates boards
	populate_plain_board(user_board);
	populate_mines_board(mines);
	
	// Start screen
	cout << "Let's play minesweeper!\n";
	print_board(user_board);
	
	// Game loop
	while (!win(user_board, mines))
	{

		int row, col;
		// Guarantees that row and col combination has not been used
		do
		{
			// Guarantees that row and col will be within the array
			do
			{
				cout << "Enter a valid row number" << endl;
				cin >> row;
			} while (row < 0 || row >= DIMEN);
                	do
                	{
                	        cout << "Enter a valid column number" << endl;
                        	cin >> col;
                	} while (col < 0 || col >= DIMEN);
		} while (user_board[row][col] != UNSEEN);

		// If a mine is selected, ends the game and shows all mines
		if (lose(mines, row, col))
		{
			for (int i = 0; i < DIMEN; i++)
			{
				for(int j = 0; j < DIMEN; j++)
				{
					if (mines[i][j] == MINE)
						user_board[i][j] = MINE;
				}
			}
			print_board(user_board);
			cout << "You hit a mine! You lose!" << endl;
			break;
		}
		// If a mine is not selected, shows number of mines in vicinity
		else
		{
			replace(user_board, mines, row, col);	
			print_board(user_board);
		}
	}
	// Winning outcome
	if (win(user_board, mines))
		cout << "Congratulations! You win!" << endl;
	return 0;
}


// Function: populate_plain_board
// Input: 2d array of chars
// Returns: nothing
// Does: puts the UNSEEN char in all squares
void populate_plain_board(char board[][DIMEN])
{
    for (int i = 0; i < DIMEN; i++)
        for (int j = 0; j < DIMEN; j++)
            board[i][j] = UNSEEN;
}

// Function print_board
// Input: 2d array of chars
// Returns: nothing
// Does: Prints the given 2d array 
//		 as well as headers for indices
void print_board(char board[][DIMEN])
{
	cout << "  ";
    for (int i = 0; i < DIMEN; i++)
        cout << i << " ";
	cout << endl;

    for (int i = 0; i < DIMEN; i++)
    {
		cout << i << " ";
        for (int j = 0; j < DIMEN; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Fills up a board with mines
void populate_mines_board(char board[][DIMEN])
{
    int numMines = 0;
    for (int i = 0; i < DIMEN; i++)
    {
	for (int j = 0; j < DIMEN; j++)
	{	
		// Creates a random number based on board size that determines
		// if the square will be a mine or not
		int mineChance = rand() % 100 + 1;
        	if (numMines < MAX_MINES && mineChance < 25)
		{
			board[i][j] = MINE;
			numMines++;	
		}
		else
		{
			board[i][j] = UNSEEN;
		}
	}
    }
}

// Determines if the player has won
bool win(char board[][DIMEN], char mines[][DIMEN])
{
	for (int i = 0; i < DIMEN; i++)
	{
		for (int j = 0; j < DIMEN; j++)
		{
			if (board[i][j] == UNSEEN && mines[i][j] == UNSEEN)
				return false;
		}
	}
	return true;
}

// Determines if the player has lost
bool lose(char mines[][DIMEN], int row, int col)
{
	if (mines[row][col] == MINE)
	{
		return true;
	}
	return false;
}

// Replaces a square on the board with the number of mines in its vicinity
void replace(char board[][DIMEN], char mines[][DIMEN], int row, int col)
{
	int vicinityMines = 0;
	// Loops through 3x3 vicinity and increments vicinityMines if there
	// is a mine in the region
	for (int i = row - 1; i <= row + 1; i++)
	{
		for (int j = col - 1; j <= col + 1; j++)
		{
			if (i >= 0 && j >= 0 && i < DIMEN && j < DIMEN)
			{
				if (mines[i][j] == MINE)
					vicinityMines++;
			}
		}
	}
	// Inserts the ASCII value of the number into the array
	board[row][col] = vicinityMines + 48;
}
