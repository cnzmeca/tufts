#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include "Game.h"
#include "Board.h"
using namespace std;

int main()
{
	// Creates random seed
	srand(time(NULL));
	
	// Gets name
        cout << "Welcome to 2048! What is your name?" << endl;
	string name;
	cin >> name;
	
	// Gets board size
	cout << "Okay, " << name << ". Enter a board size." << endl;
        int size;
	cin >> size;
        if (size <= 1)
        {
                cout << "Invalid board size. Board size set to 4." << endl;
                size = 4;
        }
	
	// Creates and sets up objects
	Game game = Game();
	game.readInHighscores();	
	Board gameboard = Board(size);
       	gameboard.setupBoard();

	game.printHighscores(); 	
	// Game loop
	while(gameboard.gameOver() == false)
        {
                gameboard.printBoard();

                char kp;
                cin >> kp;
                
		// Exits game loop
		if (kp == 'q')
		{
			break;
		}

		// Prints highscores
		else if (kp == 'h')
			game.printHighscores();
		
		// Executes desired move
                else if (kp == 'w' || kp == 'a' || kp == 's' || kp == 'd')
                {
		        gameboard.moveBoard(kp);
			
			// Creates new random Tile after move
			bool newTile = false;
			while (!newTile)
			{
				int s = gameboard.getSize();
				int xR = rand()%(gameboard.getSize());
				int yR = rand()%(gameboard.getSize());
				int valR = rand()%10;
				int target = gameboard.getElement(xR,yR);
				
				if ((xR == 0 || yR == 0 || xR == s-1 ||
				yR == s-1) && target == 0)
				{
					if (valR == 0)
						gameboard.setElement(xR,yR,4);
					else
						gameboard.setElement(xR,yR,2);
					newTile = true;
				}
			}
		}
		// Default
		else
                        cout << "Try again." << endl;
        }
	
	// Game over details
	int finalScore = gameboard.getScore();
	cout << "Game over. Your final score was " << finalScore  << endl;
	game.writeToHighscores(name, finalScore);
	game.readInHighscores();
	game.printHighscores();

        return 0;
}
