#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
using namespace std;

// Constructor
Game::Game()
{
	highscoreVals = NULL;
	highscoreNames = NULL;
	highscoresLength = 0;
}

// Destructor
Game::~Game()
{
	delete[] highscoreVals;
	delete[] highscoreNames;
}

// Reads in highscores from file
void Game::readInHighscores()
{
	ifstream infile;
        infile.open(FILENAME);
	
	// Gets highscoresLength
	infile >> highscoresLength;
	
	// Allocates memory
	highscoreNames = new string[highscoresLength];
	highscoreVals = new int[highscoresLength];
	
	// Reads in data
	for (int i = 0; i < highscoresLength; i++)
	{
		infile >> highscoreNames[i] >> highscoreVals[i];
	}
	infile.close();
}

// Writes highscores to file
void Game::writeToHighscores(string name, int score)
{
	ofstream outfile;
	outfile.open(FILENAME);

	// Writes new highscoresLength
	outfile << highscoresLength+1 << endl;
	
	// Writes highscores with new score added
	if (highscoresLength == 0)
	{
		outfile << name << " " << score << endl;
	}
	else
	{
		// Iterates to place new score in appropiate location
		for (int i = 0; i < highscoresLength; i++)
		{
			if (score > highscoreVals[i])
			{
				outfile << name << " " << score << endl;
				for (int j = i; i < highscoresLength; i++)
				{
					outfile << highscoreNames[j] << " "
					<< highscoreVals[j] << endl;
				}
				break;
			}
			else
			{
				outfile << highscoreNames[i] << " "
				<< highscoreVals[i] << endl;
			}
		}
		// Edge case solution
		if (highscoreVals[highscoresLength-1] >= score)
			outfile << name << " " << score << endl;
	}
	outfile << "-1";
	outfile.close();
}

// Prints highscores
void Game::printHighscores()
{
	cout << "Highscores:" << endl;
	
	// Prints all scores if less than 5 scores
	if (highscoresLength < 5)
	{
		for (int i = 0; i < highscoresLength; i++)
		{
		cout << highscoreNames[i] << " - " << highscoreVals[i] << endl;
		}
	}

	// Prints 5 scores if 5 or more
	else
	{
                for (int i = 0; i < 5; i++)
                {
                cout << highscoreNames[i] << " - " << highscoreVals[i] << endl;
                }
        }
	cout << endl;
}
